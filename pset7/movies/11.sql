-- list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated

SELECT title
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
JOIN ratings ON movies.id = ratings.movie_id
WHERE people.name LIKE "Chadwick Boseman"
ORDER BY ratings.rating DESC
LIMIT 5;