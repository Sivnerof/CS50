-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Keep a log of any SQL queries you execute as you solve the mystery.

-- All we know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street
    SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";

        -- description
        -- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
        -- Interviews were conducted today with three witnesses who were present at the time —
        -- each of their interview transcripts mentions the courthouse.

-- Given above information I'm going to next query the interviews table.
    SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28 AND transcript like "%courthouse%"

        -- name | transcript
        -- Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
        -- If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

        -- Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse,
        -- I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

        -- Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
        -- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
        -- The thief then asked the person on the other end of the phone to purchase the flight ticket.

        -- Witness Ruth brought up security footage, query courthouse security logs.
        -- Witness Eugene brought up ATM withdrawal, query ATM transactions.
        -- Witness Raymond brought up phone calls, flights and the purchasing tickets, query phone calls, flights?

-- Query courthouse security logs.
    SELECT license_plate, activity FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

        -- license_plate | activity
        -- 5P2BI95 | exit
        -- 94KL13X | exit
        -- 6P58WS2 | exit
        -- 4328GD8 | exit
        -- G412CB7 | exit
        -- L93JTIZ | exit
        -- 322W7JE | exit
        -- 0NTHK55 | exit

-- Query atm transactions
    SELECT transaction_type, account_number, amount FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "courthouse";

        -- transaction_type | account_number | amount
        -- withdraw | 28500762 | 48
        -- withdraw | 28296815 | 20
        -- withdraw | 76054385 | 60
        -- withdraw | 49610011 | 50
        -- withdraw | 16153065 | 80
        -- deposit | 86363979 | 10
        -- withdraw | 25506511 | 20
        -- withdraw | 81061156 | 30
        -- withdraw | 26013199 | 35

-- Query phone calls
    SELECT caller, receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;

        -- caller | receiver
        -- (130) 555-0289 | (996) 555-8899
        -- (499) 555-9472 | (892) 555-8872
        -- (367) 555-5533 | (375) 555-8161
        -- (499) 555-9472 | (717) 555-1342
        -- (286) 555-6063 | (676) 555-6554
        -- (770) 555-1861 | (725) 555-3243
        -- (031) 555-6622 | (910) 555-3251
        -- (826) 555-1652 | (066) 555-9701
        -- (338) 555-6650 | (704) 555-2131

-- Find out who owns those license plates
    SELECT name, phone_number, passport_number, license_plate FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25);

        -- name | phone_number | passport_number | license_plate
        -- Patrick | (725) 555-4692 | 2963008352 | 5P2BI95
        -- Amber | (301) 555-4174 | 7526138472 | 6P58WS2
        -- Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
        -- Roger | (130) 555-0289 | 1695452385 | G412CB7
        -- Danielle | (389) 555-5198 | 8496433585 | 4328GD8
        -- Russell | (770) 555-1861 | 3592750733 | 322W7JE
        -- Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
        -- Ernest | (367) 555-5533 | 5773159633 | 94KL13X


-- Find out who owns those phone numbers


-- Find out who owns those bank accounts








    -- executing .tables will list all of the tables in the database.
    -- executing .schema TABLE_NAME



