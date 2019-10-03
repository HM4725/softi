USE Pokemon;


# 1
SELECT T.name
FROM Trainer T, CatchedPokemon P
WHERE T.id = P.owner_id
GROUP BY T.id
HAVING COUNT(*)>=3
ORDER BY COUNT(*) DESC;

# 2
SELECT P.name
FROM Pokemon P,
	 (SELECT type
	  FROM Pokemon
	  GROUP BY type
	  ORDER BY COUNT(*) DESC LIMIT 2
	 ) AS HTypes
WHERE P.type=HTypes.type
ORDER BY P.name ASC;

# 3
SELECT name
FROM Pokemon
WHERE name LIKE '_o%'
ORDER BY name ASC;

# 4
SELECT nickname
FROM CatchedPokemon
WHERE level>=50
ORDER BY nickname ASC;

# 5
SELECT name
FROM Pokemon
WHERE CHAR_LENGTH(name)=6
ORDER BY name ASC;

# 6
SELECT name
FROM Trainer
WHERE hometown='Blue City'
ORDER BY name ASC;

# 7
SELECT DISTINCT hometown
FROM Trainer
ORDER BY hometown ASC;

# 8
SELECT AVG(level)
FROM Trainer, CatchedPokemon
WHERE Trainer.id=CatchedPokemon.owner_id
	AND name='Red';

# 9
SELECT nickname
FROM CatchedPokemon
WHERE nickname NOT LIKE 'T%'
ORDER BY nickname ASC;

# 10
SELECT nickname
FROM CatchedPokemon
WHERE level>=50
	AND owner_id>=6
ORDER BY nickname ASC;

# 11
SELECT id,name
FROM Pokemon
ORDER BY id ASC;

# 12
SELECT nickname
FROM CatchedPokemon
WHERE level<=50
ORDER BY level ASC;

# 13
SELECT P.name, P.id
FROM Trainer T, Pokemon P, CatchedPokemon CP
WHERE P.id=CP.pid
	AND T.id=CP.owner_id
	AND T.hometown='Sangnok City'
ORDER BY P.id ASC;

# 14
SELECT CP.nickname
FROM Pokemon P, CatchedPokemon CP, Gym G
WHERE G.leader_id=CP.owner_id
	AND CP.pid=P.id
	AND P.type='Water'
ORDER BY CP.nickname ASC;

# 15
SELECT COUNT(*)
FROM CatchedPokemon CP, Evolution E
WHERE CP.pid=E.before_id;

# 16
SELECT COUNT(*)
FROM Pokemon
WHERE type='Water'
	OR type='Electric'
	OR type='Psychic';

# 17
SELECT COUNT(DISTINCT CP.pid)
FROM Trainer T, CatchedPokemon CP
WHERE T.hometown='Sangnok City'
	AND T.id=CP.owner_id;

# 18
SELECT CP.level
FROM Trainer T, CatchedPokemon CP
WHERE hometown='Sangnok City'
	AND T.id=CP.owner_id
ORDER BY CP.level DESC LIMIT 1;

# 19
SELECT COUNT(DISTINCT P.type)
FROM Gym G, CatchedPokemon CP, Pokemon P
WHERE G.city='Sangnok City'
	AND G.leader_id=CP.owner_id
	AND P.id=CP.pid;

# 20
SELECT T.name, COUNT(*)
FROM Trainer T, CatchedPokemon CP
WHERE T.id=CP.owner_id
	AND T.hometown='Sangnok City'
GROUP BY T.id
ORDER BY COUNT(*) ASC;

# 21
SELECT name
FROM Pokemon
WHERE name LIKE 'A%'
	OR name LIKE 'E%'
	OR name LIKE 'U%'
	OR name LIKE 'I%'
	OR name LIKE 'O%';

# 22
SELECT type, COUNT(*)
FROM Pokemon
GROUP BY type
ORDER BY COUNT(*) ASC, type ASC;

# 23
SELECT name
FROM Trainer
WHERE id IN (
	SELECT owner_id
	FROM CatchedPokemon
	WHERE level<=10
)
ORDER BY name;

# 24
SELECT C.name, AVG(CP.level)
FROM City C, CatchedPokemon CP, Trainer T
WHERE C.name=T.hometown
	AND CP.owner_id=T.id
GROUP BY C.name
ORDER BY AVG(CP.level) ASC;

# 25
SELECT DISTINCT P.name
FROM Trainer T, CatchedPokemon CP, Pokemon P
WHERE P.id=CP.pid
	AND T.id=CP.owner_id
	AND T.hometown='Sangnok City'
	AND CP.pid in (
		SELECT CP.pid
		FROM Trainer T, CatchedPokemon CP
		WHERE T.id=CP.owner_id
			AND T.hometown='Brown City'
	)
ORDER BY P.name ASC;

# 26
SELECT Pokemon.name
FROM CatchedPokemon, Pokemon
WHERE CatchedPokemon.pid = Pokemon.id
	AND CatchedPokemon.nickname LIKE '% %'
ORDER BY name DESC;

# 27
SELECT T.name, MAX(CP.level)
FROM Trainer T, CatchedPokemon CP
WHERE T.id=CP.owner_id
GROUP BY T.name HAVING COUNT(*)>=4
ORDER BY T.name ASC;

# 28
SELECT T.name, AVG(CP.level)
FROM Trainer T, CatchedPokemon CP, Pokemon P
WHERE T.id=CP.owner_id
	AND CP.pid=P.id
	AND ( P.type='Normal'
		OR P.type='Electric'
	)
GROUP BY T.id
ORDER BY AVG(CP.level) ASC;

# 29
SELECT P.name, T.name, C.description
FROM Pokemon P, Trainer T, CatchedPokemon CP, City C
WHERE CP.owner_id=T.id
	AND CP.pid=P.id
	AND T.hometown=C.name
	AND P.id=152
ORDER BY CP.level DESC;

# 30
SELECT P1.id, P1.name, P2.name, P3.name
FROM Pokemon P1, Pokemon P2, Pokemon P3, Evolution E1, Evolution E2
WHERE E1.after_id=E2.before_id
	AND P1.id=E1.before_id
	AND P2.id=E1.after_id
	AND P3.id=E2.after_id
ORDER BY P1.id ASC;


# 31
SELECT name
FROM Pokemon
WHERE id>=10
	AND id<100
ORDER BY name ASC;

# 32
SELECT name
FROM Pokemon
WHERE id NOT IN (
	SELECT pid
	FROM CatchedPokemon
)
ORDER BY name ASC;

# 33
SELECT SUM(level)
FROM Trainer, CatchedPokemon
WHERE Trainer.id=owner_id
	AND name='Matis';

# 34
SELECT name
FROM Gym, Trainer
WHERE id=leader_id
ORDER BY name ASC;

# 35
SELECT P.type, COUNT(*)/S.sum*100 AS rate
FROM Pokemon P, (
	SELECT COUNT(*) AS sum
	FROM Pokemon
) AS S
GROUP BY P.type
ORDER BY rate DESC LIMIT 1;

# 36
SELECT T.name
FROM Trainer T, CatchedPokemon CP
WHERE T.id=CP.owner_id
	AND CP.nickname LIKE 'A%'
GROUP BY T.id
ORDER BY T.name ASC;

# 37
SELECT T.name, SUM(CP.level) AS sum
FROM Trainer T, CatchedPokemon CP
WHERE CP.owner_id=T.id
GROUP BY T.id
ORDER BY sum DESC LIMIT 1;

# 38
SELECT P.name
FROM Evolution E, Pokemon P
WHERE E.after_id NOT IN (
	SELECT E2.after_id
	FROM Evolution E1, Evolution E2
	WHERE E1.after_id=E2.before_id
)
	AND E.after_id=P.id
ORDER BY P.name ASC;

# 39
SELECT T.name
FROM CatchedPokemon CP1, CatchedPokemon CP2, Trainer T
WHERE CP1.id<>CP2.id
	AND CP1.pid=CP2.pid
	AND CP1.owner_id=CP2.owner_id
	AND CP1.owner_id=T.id
GROUP BY T.id
ORDER BY T.name ASC;

# 40
SELECT T.hometown, CP.nickname
FROM (
	SELECT T.hometown, MAX(CP.level) AS max
	FROM CatchedPokemon CP, Trainer T
	WHERE CP.owner_id=T.id
	GROUP BY T.hometown
) MX, CatchedPokemon CP, Trainer T
WHERE CP.owner_id=T.id
	AND MX.hometown=T.hometown
	AND MX.max=CP.level
ORDER BY T.hometown ASC;
