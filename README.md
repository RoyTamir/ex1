# ex1

## Advanced Programming 1 exercise 1

### Implementation:

#### Matrix struct:

- pointer to double (double\* topLeft)
-- actually array of doubles of size (width * hight)
-- the pointer just points to the first one
- height of the matrix (int height)
- width of the matrix (int width)
> typedef struct Matrix {
>     double* topLeft;
>     int width, height;
> } Matrix;

#### Access to array elements:
To implement the functions we must have access to the matrix's values.
We can access the elements through Matrix -> topLeft but we need to keep the original pointer in place.
The solution is to create a new pointer and set it to Matrix -> topLeft as such:
> double\* help = matrix -> topLeft;
now we can change the new pointer's (help) value to access the matrix's elements.
