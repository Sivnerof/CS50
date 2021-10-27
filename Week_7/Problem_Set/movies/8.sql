    -- In 8.sql, write a SQL query to list the names of all people who starred in Toy Story.
    -- Your query should output a table with a single column for the name of each person.

SELECT name FROM people JOIN stars ON people.id = stars.person_id WHERE stars.movie_id = (SELECT id FROM movies WHERE title = "Toy Story");