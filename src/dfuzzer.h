/** @file dfuzzer.h */
/*

	dfuzzer - tool for testing processes communicating through D-Bus.
	Copyright (C) 2013  Matus Marhefka

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef DFUZZER_H
#define DFUZZER_H

#define MINLEN 256				// minimal buffer size for generated strings
#define MAXLEN 256			// maximum length of strings containing D-Bus name,
							// interface and object path


/** Structure containing D-Bus name, object path and interface of process.
*/
struct fuzzing_target {		// names on D-Bus have the most MAXLEN characters
	char name[MAXLEN];
	char obj_path[MAXLEN];
	char interface[MAXLEN];
};


/**
	@function Function is called when SIGINT signal is emitted. It sets
	flag df_exit_flag for fuzzer to know, that it should end testing, free
	memory and exit.
	@param sig Catched signal number
*/
void df_signal_handler(int sig);

/**
	@function Displays an error message and exits with error code 1.
	@param message Error message which will be printed before exiting program
	@param error Pointer on GError structure containing error specification
*/
void df_error(char *message, GError *error);

/**
	@function Opens process status file.
	@param pid PID - identifier of process
	@return FD of status file on success, -1 on error
*/
int df_open_proc_status_file(int pid);

/**
	@function Parses program options and stores them into struct fuzzing_target.
	If error occures function ends program.
	@param argc Count of options
	@param argv Pointer on strings containing options of program
	@param log_file File for logs
	@param buf_size Maximum buffer size for generated strings
	by rand module (in Bytes)
	@param mem_limit Memory limit for tested process in kB
*/
void df_parse_parameters(int argc, char **argv, char **log_file,
						long *buf_size, long *mem_limit);

/**
	@function Prints help.
	@param name Name of program
*/
void df_print_help(char *name);

#endif