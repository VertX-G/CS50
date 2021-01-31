-- list the names of all people who starred in a movie released in 2004, ordered by birth year

-- SELECT name
-- FROM movies
-- JOIN stars ON movies.id = stars.movie_id
-- JOIN people ON stars.person_id = people.id
-- WHERE movies.year = 2004
-- ORDER BY people.birth;

SELECT name FROM people WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT id FROM movies WHERE year = 2004)) ORDER BY birth;