1)In the head module using functions "scan_names( struct company)" (*), "scan_tax(struct company, int)" (**) and 
"scan_dates(struct company, int)" (***) enter information about structure's data.

2)Enter the number of the month and validated by "valid_input(char* month_name)"(****) function

3)Using "Selection sort" elements of array of structures are sorted by maximum taxes to the fifth largest element

4)Using "Selection sort" five largest elements are sorted by first name letter.

5) Data of fields of five structures with max taxes displayed on the screen alphabetically.


(*) - /// allocates a temporary array that records the data on behalf of the company to the line that starts 
with ".", after which the appropriate amount of memory allocated in the passed array, and returns the value of 
the number of firms.

(**) - Into the function passed the number of firms and an array of structures, after which there is input tax for
each firm.

(***) - Into the function passed the number of firms and an array of structures, then function using the
"valid_input(char* month_name)"(****) scan last and actual date of the tax payment.

(****) -  Using initialized array of months, function compares entered in her body  month with elements of array and
in the case of coincidence returns the number of the month. Otherwise, the entry and comparison with the array anew.
