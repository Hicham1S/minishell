int	check_quotation(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		i++;
	}
	return (quote == 0);
}

// #include <stdio.h>
// int main(void)
// {
//     char *test1 = "This is a 'test string' with closed single quotes.";
//     char *test2 = "This is a 'test string with unclosed single quotes.";
//     char *test3 = "This is a \"test string\" with closed double quotes.";
//     char *test4 = "This is a \"test string with unclosed double quotes.";
//     char *test5 = "This is a 'mix of \"single\" and 'double\" quotes.";
    
//     printf("Test 1: %s => %s\n", test1, check_quotation(test1) ? "Passed" : "Failed");
//     printf("Test 2: %s => %s\n", test2, check_quotation(test2) ? "Passed" : "Failed");
//     printf("Test 3: %s => %s\n", test3, check_quotation(test3) ? "Passed" : "Failed");
//     printf("Test 4: %s => %s\n", test4, check_quotation(test4) ? "Passed" : "Failed");
//     printf("Test 5: %s => %s\n", test5, check_quotation(test5) ? "Passed" : "Failed");

//     return 0;
// }
