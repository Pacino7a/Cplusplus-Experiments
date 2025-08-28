#include <iostream>
#include <cstdarg> // for ellipsis

double findAverage(int count,...) // this function takes a <variable number> of parameters
{
    int sum{};

    // va_list, va_start, va_arg, va_end For ellipsis Access (all marcos)
    std::va_list list; // access the ellipsis array

    va_start(list, count);  // initialze the ellipsis list, the first is our initializing target and the second one is the last
                            // non-ellipsis parameter (get the values in)

    for (int i = 0; i < count; ++i)
    {
        sum += va_arg(list, int); // we use va_arg to extract the values which we initialzed before
    }

    va_end(list); // clean up the list when we're done

    return static_cast<double>(sum) / count;
}

double findAverage(std::string_view decoder,...) // this function takes a <variable number> of parameters
{
    double sum{};

    // va_list, va_start, va_arg, va_end For ellipsis Access (all marcos)
    std::va_list list; // access the ellipsis array

    va_start(list, decoder);  // initialze the ellipsis list, the first is our initializing target and the second one is the last
                            // non-ellipsis parameter (get the values in)

    for (auto codetype:decoder)
    {
        switch (codetype)
		{
		case 'i':
			sum += va_arg(list, int);
			break;

		case 'd':
			sum += va_arg(list, double);
			break;
		} // we use va_arg to extract the values which we initialzed before
    }

    va_end(list); // clean up the list when we're done

    return sum / static_cast<double>(std::size(decoder));
}

// The ellipsis must be the last parameter
// double findAverage(int first, ...)
// {
// 	// We have to deal with the first number specially
// 	int sum{ first };

// 	// We access the ellipsis through a va_list, so let's declare one
// 	std::va_list list;

// 	// We initialize the va_list using va_start.  The first argument is
// 	// the list to initialize.  The second argument is the last non-ellipsis
// 	// parameter.
// 	va_start(list, first);

// 	int count{ 1 };
// 	// Loop indefinitely
// 	while (true)
// 	{
// 		// We use va_arg to get values out of our ellipsis
// 		// The first argument is the va_list we're using
// 		// The second argument is the type of the value
// 		int arg{ va_arg(list, int) };

// 		// If this parameter is our sentinel value, stop looping
// 		if (arg == -1)
// 			break;

// 		sum += arg;
// 		++count;
// 	}

// 	// Cleanup the va_list when we're done.
// 	va_end(list);

// 	return static_cast<double>(sum) / count;
// }

int main()
{
    int value{10};
    std::cout << findAverage(5, 1, 2, 3, 4, 5) << '\n';
    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';
    std::cout << findAverage("iiiddi", 1, 2, 3, 4.2, 5.6, 7) << '\n';
    std::cout << findAverage(5, 1, 2.3,"hello",&value,'G') << '\n'; // what a mess here, but this compiles just fine (garbage in and garbage out)

    return 0;
}
