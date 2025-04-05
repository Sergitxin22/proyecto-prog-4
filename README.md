# shell
A C-programmed, database-driven simple shell.


This shell provides the most fundamental commands a shell requires to perform simple tasks in an operative system. It also features a database system to efficiently store shell data.

## Core functionalities
- Reading/writing files
- Directory creation
- Filesystem navigation
- A user system
- Admin privileges
- Command log

## Shell database
The shell features a a local, single-file sqlite3 database to efficiently store command documentation and user data. To do so, it uses the [libsqlite3](https://github.com/LuaDist/libsqlite3) sqlite3 driver, owned by [The Lua Language Distribution](https://luadist.org/).

## Build
### Compilation
In order to compile the project, you can execute the command `make` in the root directory of the repository. The Makefile will generate an executable binary called `shell.out`, which can be executed normally. If any issues arise, you can compile the shell by executing the first commented line in `Makefile`, which will compile the source files manually with `gcc`.

### Database initialization
When first executing the shell, if the database is not created, the user functionalities and documentation will not be avaliable. To create the database automatically, you can run `./shell.out --create-database`, which will create the tables, insert the command documentation and generate two users for testing. "alice", an admin, and "bob", not an admin. The password for both users is "password123". After initializing the database, the shell is ready to be executed normally. Executing the mentioned command again after creation will result in a datababase reset.

### Configuration file
The configuration file (`conf.h`) allows the modification of certain configuration variables. In the current version, you can modify the database path with `DB_PATH` and the log file path with `LOG_PATH` 

## Documentation
To see every available command in the shell, you can execute the `printcommands`command:
```
shell > printcommands
```
To read the documentation of a specific command, you can run:
```
shell > man <command>
```

## License
This repository follows the GNU General Public License (GPLv3). Everyone is permitted to copy and distribute verbatim copies of this license document, but changing it is not allowed. For more information, refer to the [Free Software Foundation website](https://fsf.org/) or read `LICENSE`.


