-- FIX --
-- list the names of all people who have directed a movie that received a rating of at least 9.0

SELECT name FROM people WHERE id = (SELECT person_id FROM directors WHERE movie_id = (SELECT movie_id FROM ratings WHERE rating >= 9.0));

SELECT name
FROM ratings
JOIN directors ON movies.id = directors.movie_id
JOIN people ON directors.person_id = people.id
JOIN ratings ON ratings.movie_id = movies.id
WHERE ratings.rating >= 9.0;