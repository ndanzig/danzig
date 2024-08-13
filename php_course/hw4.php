<html>
<body>
<h1>Exercises/Homework</h1>
<p>Below you have a table definition and some sql statements. For each statement draw the resulting database table.(assume that the instructions are performed in sequence)</p>
<pre>
CREATE TABLE example_table (
  id int(10) DEFAULT '0' NOT NULL auto_increment,
  status tinyint(3),
  username varchar(20),
  email varchar(255),
  description text,
  datecreated datetime,
  lastupdated datetime,
  PRIMARY KEY (id)
);
</pre>
<table border="1">
<tr><td colspan="7">example_table</td></tr>
<tr><td>id</td><td>status</td><td>username</td><td>email</td><td>description</td><td>datecreated</td><td>lastupdated</td></tr>
</table>

<pre>
INSERT INTO example_table (id,status,username,datecreated) 
            VALUES (NULL,1,'testuser',NOW());

DELETE FROM example_table;

INSERT INTO example_table 
            VALUES (NULL,1,'testuser','testuser@mysql.com',
                    'This is a description.',NOW(),NULL);
INSERT INTO example_table 
            VALUES (NULL,1,'testuser','testuser@mysql.com',
                    'This is a description.',NOW(),NULL);

DELETE FROM example_table WHERE id=1;

INSERT INTO example_table 
            VALUES (NULL,1,'usertest','usertest@mysql.com',
                    'This is a description.',NOW(),NULL);

INSERT INTO example_table 
            VALUES (NULL,1,'auser','testuser@mysql.com',
                    'This is a description.',NOW(),NULL);

DELETE FROM example_table WHERE username LIKE 'u%';

INSERT INTO example_table 
            VALUES (NULL,1,'user','testuser@mysql.com',
                    'This is a description.',NOW(),NULL);

UPDATE example_table SET username='newusername',lastupdated=NOW() WHERE id=1;

SELECT * FROM example_table;

SELECT id,status,username FROM example_table;

SELECT id,status,username FROM example_table WHERE username='user';

SELECT id,status,username FROM example_table WHERE username='user' 
       ORDER BY datecreated,lastupdated;

SELECT COUNT(*) FROM example_table;

SELECT id,status,username FROM example_table 
       WHERE (username='user' AND password='pass');

SELECT id,status,username FROM example_table WHERE username LIKE 'u%';

SELECT id,status,username FROM example_table WHERE username LIKE 'u%' 
       LIMIT 0,5;

SELECT id,status,username FROM example_table WHERE username LIKE '%u' 
       ORDER BY username,lastupdated DESC LIMIT 1,6;
</pre>
</body>
</html>