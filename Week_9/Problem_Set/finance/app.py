import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Query user purchases/balance
    stocks = db.execute(
        "SELECT symbol, name, price, SUM(shares) AS sum_total FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
    funds = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    balance = funds

    for stock in stocks:
        balance += stock["price"] * stock["sum_total"]

    # Pass purchases/balance to index
    return render_template("index.html", stocks=stocks, funds=funds, balance=balance, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        # Ensure symbol field is not blank
        if not request.form.get("symbol"):
            return apology("Symbol can not be blank")

        # Ensure symbol is valid
        elif not lookup(request.form.get("symbol")):
            return apology("Invalid symbol")

        # Ensure shares are not blank
        elif not request.form.get("shares"):
            return apology("Shares can not be empty")

        # Make sure shares are positive integers
        elif not request.form.get("shares").isdigit():
            return apology("Minimum must be one share")

        # Query cash amount
        balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # Save stock information
        stock_name = lookup(request.form.get("symbol"))["name"]
        stock_price = lookup(request.form.get("symbol"))["price"]
        total_cost = stock_price * int(request.form.get("shares"))

        # Check for available funds
        if balance < total_cost:
            return apology("Insufficient funds")

        # Complete transaction
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", balance - total_cost, session["user_id"])
            db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                       session["user_id"], stock_name, request.form.get("shares"), stock_price, 'buy', request.form.get("symbol").upper())

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Query transactions
    transactions = db.execute(
        "SELECT type, symbol, price, shares, time, name FROM transactions WHERE user_id = ?", session["user_id"])

    # Show transaction history
    return render_template("history.html", usd=usd, transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        # Ensure sybmol field is not empty
        if not request.form.get("symbol"):
            return apology("Symbol can not be blank")

        # Ensure symbol is valid
        elif not lookup(request.form.get("symbol")):
            return apology("Invalid symbol")

        # Save symbol
        ticker = lookup(request.form.get("symbol"))

        # Pass symbol to quoted template
        return render_template("quoted.html", ticker=ticker, usd=usd)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("username can not be blank", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("password can not be blank", 400)

        # Ensure password confirmation field not blank
        elif not request.form.get("confirmation"):
            return apology("password confirmation can not be blank", 400)

        # Check for username already existing
        user_names = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(user_names) != 0:
            return apology("username already exists", 400)

        # Make sure passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Create User in SQL database and reroute to login
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get(
            "username"), generate_password_hash(request.form.get("password")))
        return redirect("/")

    # Keep user on registration form
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Check for negative or invalid shares
    if request.method == "POST":

        if int(request.form.get("shares")) < 1:
            return apology("Enter valid amount")

        # Save stock information
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        stock_price = lookup(symbol)["price"]
        stock_name = lookup(symbol)["name"]
        stock_sale = stock_price * shares
        sellable_shares = db.execute(
            "SELECT shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", session["user_id"], symbol)[0]["shares"]
        cash_balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # Ensure user has enough shares available to sell
        if sellable_shares < shares:
            return apology("Not enough shares")

        # Execute transaction
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_balance + stock_sale, session["user_id"])
        db.execute("INSERT into transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], stock_name, -shares, stock_price, "sell", symbol.upper())

        # Success
        return redirect("/")

    else:
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", session["user_id"])
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
