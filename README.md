# Pipe operator

Pipex reproduces the behaviour of the shell pipe | command in C.
It launches as `./pipex infile cmd1 cmd2 outfile` and behaves as this line does in the shell `< infile cmd1 | cmd2 > outfile`.

|    Project Name    |                                                                       pipex                                                                      |
| :----------------: | :-------------------------------------------------------------------------------------------------------------------------------------------------: |
|    Description     |                                             My implementation of the pipe operator                                              |
|    Technologies    | <a href="#"><img alt="C" src="https://custom-icon-badges.demolab.com/badge/C-03599C.svg?logo=c-in-hexagon&logoColor=white&style=for-the-badge"></a> |
| External libraries |     open(), close(), read(), write(), malloc(), free(), perror(), strerror(), access(), dup(), dup2(), execve(), exit(), fork(), pipe(), unlink(), wait(), waitpid()      |

## Usage

```bash
  gcl https://github.com/trobert42/pipex.git
  cd pipex
  make
```
Make sure you create file1 as input and the output will be displayed on the existing file2 (or it will be created) 
```bash
./pipex file1 command1 command2 file2
```
