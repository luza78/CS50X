SELECT movies.title, ratings.rating from movies, ratings
WHERE movies.id = ratings.movie_id
AND movies.year = 2010
ORDER BY rating DESC, title ASC;