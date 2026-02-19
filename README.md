![minishell](https://raw.githubusercontent.com/realgetOff/main/1af45b1706ac9c318c824c7e4c1a2a5a7abd1055/Header/minishell.png)

<p align="center">
	<img src="https://img.shields.io/badge/status-finished-cyan"/>
  <img src="https://img.shields.io/badge/evaluated-02%20%2F%2005%20%2F%202025-cyan"/>
	<img src="https://img.shields.io/badge/score-100%2F100-cyan"/>
	<img src="https://img.shields.io/badge/language-C-cyan"/>
  <img src="https://img.shields.io/badge/last_commit-april-cyan"/>
	<a href='https://profile.intra.42.fr/users/mforest-' target="_blank"><img alt='42' src='https://img.shields.io/badge/Intra-100000?style=flat-round&logo=42&logoColor=white&labelColor=000000&color=000000'/></a>
</p>

<p align="center">
	<a href="#about">About</a> •
	<a href="#how-to-use">How to use</a> •
	<a href="#mandatory">Mandatory</a> •
	<a href="#bonus">Bonus</a> •
	<a href="#norminette">Norminette</a> •
  <a href="#contributing">Contributing</a>
</p>

## ABOUT
This project consists of creating a simple shell. It serves as a practical introduction to the world of processes and file descriptors. The goal is to develop a program capable of reading commands, parsing them, and executing them, mimicking the basic behavior of Bash.

- [Subject](https://github.com/realgetOff/mini_hell/blob/master/en_subject.pdf) `PDF`

## HOW TO USE
#### 1º - Clone the repository
```bash
cd mini_hell
git clone https://github.com/realgetOff/mini_hell.git
```

#### 2º - Go to the root of the project and run the following command:

```bash
make
```

#### 3º - Launch the shell as follows:

```bash
./mini_hell
```

#### MAKEFILE RULES
`make` - Compile so_long files.

`make clean`  - Delete all .o (object files) files.

`make fclean`  - Delete all .o (object files) and .a (executable) files.

`make re` - Use rules `fclean` + `all`.

## MANDATORY
- [x] Prompt: Displays a prompt when waiting for a new command. 
- [x] History: Working command history. 
- [x] Execution: Searches and launches executables (PATH, absolute or relative paths). 
- [x] Signals: - ctrl-C displays a new prompt. 
               ctrl-D exits the shell. 
               ctrl-\ does nothing. 
- [x] Quotes: - ' (Single quotes) prevent interpretation of meta-characters.
              " (Double quotes) prevent interpretation except for $. 
- [x] Redirections: Handles <, >, >>, and << (heredoc). 
- [x] Pipes: Connects the output of a command to the input of the next. 
- [x] Environment: Handles $ expansion and $? for exit status. 

BUILT-INS
- [x] echo (with -n), cd, pwd, export, unset, env, exit. 

## BONUS
- [ ] Logical Operators: Handles && and || with parentheses for priorities. 
- [ ] Wildcards: Handles * for the current working directory. 

## NORMINETTE
> At 42 School, it is expected that almost every project is written following the Norm.
- [x] No memory leaks (except from the readline library). 
- [x] Only one global variable allowed (for signals). 
- [x] Compliance with the 42 Norm (v3). 

* [42 Norms](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf) - Information about 42 code norms. `PDF`
* [Norminette](https://github.com/42School/norminette) - Tool to respect the code norm, made by 42. `GitHub`
* [42 Header](https://github.com/42Paris/42header) - 42 header for Vim. `GitHub`

## CONTRIBUTING

If you find any issues or have suggestions for improvements, feel free to fork the repository and open an issue or submit a pull request.
> All credits go to @jotavare for the original README template.
