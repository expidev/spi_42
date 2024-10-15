/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharivon <nharivon@42student.antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 08:14:25 by nharivon          #+#    #+#             */
/*   Updated: 2024/09/10 08:14:29 by nharivon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

volatile sig_atomic_t g_received_bit = 0;

void handle_signal(int sig)
{
    static int bit_count = 0;
    static char current_char = 0;

    if (sig == SIGUSR1)
        current_char |= (0 << bit_count);
    else if (sig == SIGUSR2)
        current_char |= (1 << bit_count);

    bit_count++;
    if (bit_count == 8)
    {
        write(1, &current_char, 1);
        bit_count = 0;
        current_char = 0;
    }
}

int main(void)
{
    struct sigaction sa;

    printf("Server PID: %d\n", getpid());

    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1)
        pause();

    return 0;
}