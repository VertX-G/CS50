-- FIX --
-- list titles of all movies which starred both Johnny Depp and Helena Bonham Carter

SELECT title
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE stars.movie_id

WHERE people.name LIKE "Johnny Depp"
AND people.name LIKE "Helena Bonham Carter";
