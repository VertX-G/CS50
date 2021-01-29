-- get the name of all of the songs by "Post Malone"

SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name LIKE "Post Malone");