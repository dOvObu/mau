cmake_minimum_required(VERSION 3.0)

project(gobho)

add_executable( run
	main.cpp
	cirstr.cpp
	gswstr.cpp
	lexer_detect_keys.cpp
	lexer_without_keys.cpp
	parser_of_binary_operators.cpp
	parser_of_calls_and_unary_operators.cpp
	parser_of_conditional_and_loop_statements_and_lambda_defs.cpp
)
