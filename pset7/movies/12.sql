-- list titles of all movies which starred both Johnny Depp and Helena Bonham Carter

SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name LIKE "Johnny Depp")) AND id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name LIKE "Helena Bonham Carter"));