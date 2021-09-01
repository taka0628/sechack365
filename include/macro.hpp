#ifndef ___MACRO_HPP
#define ___MACRO_HPP

#define ERROR(comment) \
	printf("[ERROR]\n\t__%s__/__%s: %d\n\t%s\n", __FILE__, __func__, __LINE__, comment)

#define ERROR_NO_COMMENT \
	printf("[ERROR]\n\t__%s__/__%s: %d\n", __FILE__, __func__, __LINE__)

#endif