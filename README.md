# Minishell

Minishell is a lightweight Unix shell implementation written in C. It aims to replicate the functionality of the Bash shell while also supporting features such as redirection operators, pipes, and conditional execution operators (`||` and `&&`). Minishell utilizes the `readline` library for enhanced command line editing capabilities.



## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Basic Shell Commands:** Execute common shell commands such as `ls`, `cd`, `pwd`, etc.
- **Operators Support:** Use `||` and `&&` operators for conditional execution of commands.
- **Redirection Operators:** Minishell supports the following redirection operators:
  - `>`: Redirects standard output to a file, overwriting the file if it already exists.
  - `<`: Redirects standard input from a file.
  - `>>`: Appends standard output to a file, creating the file if it does not exist.
  - `<<`: Here document redirection, allowing input from multiple lines of text until a specified delimiter.
- **Pipes:** Minishell supports the pipe operator `|` for chaining multiple commands together, where the output of one command is used as the input for the next command.

## Installation

To use Minishell, follow these steps:

1. Clone or download the repository.
2. `cd minishell`
3. Run `make`

## Usage

To run Minishell, navigate to the directory where it is installed and execute the following command:

```bash
./minishell
```
Once Minishell is running, you can start entering commands just like in a regular Unix shell.

## Examples
Here are some examples of using Minishell:

```bash
$ ls -l # List files in long format
$ cd my_directory # Change directory to 'my_directory'
$ pwd # Print current working directory
$ ls non_existent_directory || echo "Directory does not exist" # Using the '||' operator
$ mkdir new_directory && cd new_directory # Using the '&&' operator
```

## Contributing

Contributions are welcome! If you want to contribute to Minishell, please follow these steps:

1. Fork the repository by clicking on the 'Fork' button on the top right corner of the page.
2. Clone the forked repository to your local machine using Git:
    ```bash
    git clone https://github.com/arsenbadalyan/minishell.git
    ```
3. Create a new branch to work on your feature or bug fix:
    ```bash
    git checkout -b feature/NewFeature
    ```
    Replace `NewFeature` with a descriptive name for your feature or bug fix.
4. Make your changes, commit them, and push your branch to GitHub:
    ```bash
    git commit -am 'Add some feature'
    git push origin feature/NewFeature
    ```
5. Go to the original repository on GitHub and click on the "New Pull Request" button to create a new pull request. Ensure that your pull request clearly explains the changes you have made.

Thank you for your contribution!

## License

This project is licensed under the [MIT License](LICENSE).
