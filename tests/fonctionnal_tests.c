/*
** EPITECH PROJECT, 2024
** Duo Stumper 2
** File description:
** tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include <unistd.h>

#include "tests.h"

static int setup_input_pipe(const char *input_str)
{
    int pipefd[2];
    pipe(pipefd);
    write(pipefd[1], input_str, strlen(input_str));
    close(pipefd[1]);

    return pipefd[0];
}

Test(exec, example1, .init = cr_redirect_stdout) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        "DESKTOP_SESSION=hyprland",
        "XCURSOR_SIZE=24",
        "XDG_SEAT=seat0",
        "PATH=/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin"
        "LESS=-R",
        "LSCOLORS=Gxfxcxdxbxegedabagacad",
        NULL
    };

    int input_fd = setup_input_pipe("echo bijour\n");
    dup2(input_fd, STDIN_FILENO);
    int ret = my_shell(env);
    cr_assert_eq(ret, 0, "Expected return value is 0 but got %d", ret);
    fflush(stdout);
    cr_assert_stdout_eq_str("bijour\n");
    close(input_fd);
}

Test(cd, example1, .init = cr_redirect_stdout) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        "DESKTOP_SESSION=hyprland",
        "XCURSOR_SIZE=24",
        "XDG_SEAT=seat0",
        "PATH=/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin"
        "LESS=-R",
        "LSCOLORS=Gxfxcxdxbxegedabagacad",
        NULL
    };

    int input_fd = setup_input_pipe("cd lib\n");
    dup2(input_fd, STDIN_FILENO);
    int ret = my_shell(env);
    cr_assert_eq(ret, 0, "Expected return value is 0 but got %d", ret);
    close(input_fd);
}

Test(cd , example2, .init = cr_redirect_stderr) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        "DESKTOP_SESSION=hyprland",
        "XCURSOR_SIZE=24",
        "XDG_SEAT=seat0",
        "PATH=/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin"
        "LESS=-R",
        "LSCOLORS=Gxfxcxdxbxegedabagacad",
        NULL
    };

    int input_fd = setup_input_pipe("cd 42sh\n");
    dup2(input_fd, STDIN_FILENO);
    my_shell(env);
    fflush(stdout);
    cr_assert_stderr_eq_str("42sh: Not a directory.\n");

    close(input_fd);
}

Test(env, example1, .init = cr_redirect_stdout) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        NULL
    };

    int input_fd = setup_input_pipe("env\n");
    dup2(input_fd, STDIN_FILENO);
    int ret = my_shell(env);
    cr_assert_eq(ret, 0, "Expected return value is 0 but got %d", ret);
    fflush(stdout);
    cr_assert_stdout_eq_str("SHELL=/usr/bin/zsh\nHYPRLAND_CMD=Hyprland\nXDG_BACKEND=wayland\n");
    close(input_fd);
}

Test(setenv, example1, .init = cr_redirect_stdout) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        NULL
    };

    int input_fd = setup_input_pipe("setenv\n");
    dup2(input_fd, STDIN_FILENO);
    int ret = my_shell(env);
    cr_assert_eq(ret, 0, "Expected return value is 0 but got %d", ret);
    fflush(stdout);
    cr_assert_stdout_eq_str("SHELL=/usr/bin/zsh\nHYPRLAND_CMD=Hyprland\nXDG_BACKEND=wayland\n");
    close(input_fd);
}

Test(setenv, example3, .init = cr_redirect_stdout) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        NULL
    };

    int input_fd = setup_input_pipe("setenv PATH test ; env\n");
    dup2(input_fd, STDIN_FILENO);
    int ret = my_shell(env);
    cr_assert_eq(ret, 0, "Expected return value is 0 but got %d", ret);
    fflush(stdout);
    cr_assert_stdout_eq_str("SHELL=/usr/bin/zsh\nHYPRLAND_CMD=Hyprland\nXDG_BACKEND=wayland\nPATH=test\n");
    close(input_fd);
}

Test(unsetenv, example1, .init = cr_redirect_stdout) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        NULL
    };

    int input_fd = setup_input_pipe("unsetenv XDG_BACKEND ; env\n");
    dup2(input_fd, STDIN_FILENO);
    int ret = my_shell(env);
    cr_assert_eq(ret, 0, "Expected return value is 0 but got %d", ret);
    fflush(stdout);
    cr_assert_stdout_eq_str("SHELL=/usr/bin/zsh\nHYPRLAND_CMD=Hyprland\n");
    close(input_fd);
}

Test(exit, example1, .init = cr_redirect_stdout) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        NULL
    };

    int input_fd = setup_input_pipe("exit\n");
    dup2(input_fd, STDIN_FILENO);
    int ret = my_shell(env);
    cr_assert_eq(ret, 0, "Expected return value is 0 but got %d", ret);
    fflush(stdout);
    cr_assert_stdout_eq_str("exit\n");
    close(input_fd);
}

Test(alias, example1, .init = cr_redirect_stdout) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        NULL
    };

    int input_fd = setup_input_pipe("alias caca=env ; caca\n");
    dup2(input_fd, STDIN_FILENO);
    int ret = my_shell(env);
    cr_assert_eq(ret, 0, "Expected return value is 0 but got %d", ret);
    fflush(stdout);
    cr_assert_stdout_eq_str("SHELL=/usr/bin/zsh\nHYPRLAND_CMD=Hyprland\nXDG_BACKEND=wayland\n");
    close(input_fd);
}

Test(set, example1, .init = cr_redirect_stdout) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        NULL
    };

    int input_fd = setup_input_pipe("set BIN = /usr/bin\n");
    dup2(input_fd, STDIN_FILENO);
    int ret = my_shell(env);
    cr_assert_eq(ret, 0, "Expected return value is 0 but got %d", ret);
    close(input_fd);
}

Test(single_right_redirection, example1, .init = cr_redirect_stdout) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        NULL
    };

    int input_fd = setup_input_pipe("env > /dev/null\n");
    dup2(input_fd, STDIN_FILENO);
    int ret = my_shell(env);
    cr_assert_eq(ret, 0, "Expected return value is 0 but got %d", ret);
}

Test(double_right_redirection, example1, .init = cr_redirect_stdout) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        NULL
    };

    int input_fd = setup_input_pipe("env >> /dev/null\n");
    dup2(input_fd, STDIN_FILENO);
    int ret = my_shell(env);
    cr_assert_eq(ret, 0, "Expected return value is 0 but got %d", ret);
}

/*
Test(single_left_redirection, example1, .init = cr_redirect_stdout) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        NULL
    };

    int input_fd = setup_input_pipe("cat < Makefile\n");
    dup2(input_fd, STDIN_FILENO);
    int ret = my_shell(env);
    cr_assert_eq(ret, 0, "Expected return value is 0 but got %d", ret);
}

Test(double_left_redirection, example1, .init = cr_redirect_stdout) {
    char *env[] = {
        "SHELL=/usr/bin/zsh",
        "HYPRLAND_CMD=Hyprland",
        "XDG_BACKEND=wayland",
        NULL
    };

    int input_fd = setup_input_pipe("cat << END\nMakefile\nEND\n");
    dup2(input_fd, STDIN_FILENO);
    int ret = my_shell(env);
    cr_assert_eq(ret, 0, "Expected return value is 0 but got %d", ret);
}
*/


