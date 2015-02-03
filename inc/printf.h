#ifndef PRINTF_H_
#define PRINTF_H_



typedef struct printf_file_s
{
	char *buffer;							///< pointer to buffer for data
	void (*put)(char);						///< put() function for writing data

	int length;								///< user's variable for current length
} printf_file_t;

/*
* \brief Simplified printtf() - prints formatted string
* \details Prints a string to stdout_ (USART). Only %s, %d, %x, %c and %%
* specifiers are supported
*
* \param [in] format is a standard format string, additional parameters
* expected - one for each specifier
* \return number of written characters
*//*-------------------------------------------------------------------------*/

int printf_(const char *format, ...);


/*------------------------------------------------------------------------*//**
* \brief Simplified sprinttf() - prints formatted string to buffer
* \details Prints a string to buffer. Only %s, %d, %x, %c and %% specifiers are
* supported
*
* \param [out] buffer is a buffer for string
* \param [in] format is a standard format string, additional parameters
* expected - one for each specifier
* \return number of written characters
*//*-------------------------------------------------------------------------*/

int sprintf_(char *buffer, const char *format, ...);


#endif /* PRINTF_H_ */
