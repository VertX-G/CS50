-- return the average energy of the songs by "Drake"

SELECT AVG(energy) FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name LIKE "Drake");