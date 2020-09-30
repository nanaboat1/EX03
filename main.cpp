#include <iostream> // the standard i/o library
#include <string> // the standard string library
#include <vector>   // standard vector library
#include <cstdlib> // for the random library
#include <cmath> // for basic math operations.



// Testing Approach, Adapted from Professor Peter Tucker in class-review.

class Triangle {

    public:
        int get_a( ) {  return side_a;  }
        int get_b()  {  return side_b;  }
        int get_c()  {  return side_c;  }

    private:
        int side_a, side_b, side_c;
        int size;

    public:

        // Default Constructor
        Triangle( ) : Triangle(1,1,1) {}

        // Parameterized Constructor
        Triangle( int a, int b, int c) : side_a(a), side_b(b), side_c(c), size(3) {}

        // Destructor
        ~Triangle( ) {};
    //


};
// Type of Triangle 
enum triangleType { NotATriangle,Scalene, Right, Isosceles, Equilateral};
/** 
 *  Code Adapted from Professor Pete's structure testing approach
*/

/**  
 *  Convert triangleType of type Enum to String
 * 
 *  @param type TriangleType 
 *  @return stringify of TriangleType
 */
std::string to_string( triangleType type) {

    switch(type) {

        case 0: return "NotATriangle";
        case 1: return "Scalene";
        case 2: return "Right";
        case 3: return "Isosceles";
        case 4: return "Equilateral";
        default: return "NotATriangle";
    }
}

// function prototypes
triangleType isTriangle( Triangle tri );
class triangleTest { 

    public:
        Triangle tri;
        triangleType expectedResult;

        triangleTest(Triangle _tri, triangleType _expR ) : tri(_tri), expectedResult(_expR) {}
    //
};

/**
 *  Get the length of the max side
 * 
 *  @param t triangle to evaluate
 *  @return the max side's length
 * 
 */
int checkMaxlength( Triangle t )  {

    if ( t.get_a() > t.get_b() && t.get_a() > t.get_c()) return t.get_a();

    if ( t.get_b() > t.get_a() && t.get_b() > t.get_c()) return t.get_b();

    if ( t.get_c() > t.get_a() && t.get_c() > t.get_b()) return t.get_c();

    return t.get_a(); // when they are all equal.
}

/** 
 * To run the tests
 * 
 *  @param test  triangleTest object
 *  
*/
void runTest( triangleTest test ) {

    triangleType actual = isTriangle(test.tri); //

    if ( actual != test.expectedResult ) {
        std::cout << "Test FAILED\n";
        std::cout << "\t<" << test.tri.get_a() << ", " << test.tri.get_b() << ", " << test.tri.get_c() << ">\n";
        std::cout << "\texp: " << to_string(test.expectedResult) << "\n";
        std::cout << "\tact: " << to_string(actual) << "\n";

    }
}
/** 
 *  Evaluates the sides of the shape to ensure no sides is <=0.
 * 
 * @tparam shape shape to be evaluated
 * @return whether sides meets criteria.
*/
bool check_shape( Triangle shape ) {

    // loop to check the length
    if( shape.get_a() <= 0 ) return false;

    if( shape.get_b() <= 0 )  return false;

    if( shape.get_c() <= 0 )  return false;  
  
    return true;
}

/** 
 *  Check if the triangle meets the inequality theorem
 * 
 *  @param  s triangle 
 *  @return  if triangle meets the criteria
*/
bool inquality_theorem( Triangle s ) {

    // Triangle Inequality Theorem
    return ( s.get_a() + s.get_b()> s.get_c() &&
    /** */   s.get_a() + s.get_c()> s.get_b() &&
    /** */   s.get_b() + s.get_c()> s.get_a());
}

/**
 *  Checks the type of the triangle 
 * @param t triangle to be evaluated
 * @return specific triangle of enum triangleType
*/

triangleType check_type( Triangle t) {

    // Check if it is equilateral
    if  ( t.get_a() == t.get_b() == t.get_c() ) return Equilateral;

    // Check if it is Isosceles
    if  ( (t.get_a()==t.get_b()&& t.get_a() != t.get_c()) || // a==b and !=c
          (t.get_b()==t.get_c()&& t.get_b() != t.get_a()) || // b==c and !=a
          (t.get_a()==t.get_c()&& t.get_a() != t.get_b())  ) // a==c and !=b
          { return Isosceles; }

    // Check if it is Right-angled triangle
    if ( checkMaxlength(t) > 0 ) {

        int max = checkMaxlength(t); // get the max length of the triangle.
        
        // Evaluating the right angle condition
        if ( max == t.get_a() ) {
            // a^2 = b^2 + b^2
            if ( std::pow(max, 2)== std::pow(t.get_b(),2)+ std::pow(t.get_c(),2)) return Right;

        } else if (max == t.get_b() ) {
            // b^2 = a^2 + c^2
            if (std::pow(max, 2)== std::pow(t.get_a(),2)+ std::pow(t.get_c(),2)) return Right;
        } else {
            // c^2 = a^2 + b^2
            if (std::pow(max, 2)== std::pow(t.get_a(),2)+ std::pow(t.get_b(),2)) return Right;
        }   
    }

    // Check if it is Scalene
    if ( t.get_a() != t.get_b() != t.get_c() ) return Scalene; 

    

    return NotATriangle;
}
/**
 *  Checks if the shape is a triangle
 *
 * @param tri triangle shape
 * @return either the sides make-up a triangle or not
 * 
 */
triangleType isTriangle( Triangle tri ) { 

    // Check the respective lengths of tri based on the expression
    // ( tri_side <= 0 )
    if ( check_shape( tri ) != true ) return NotATriangle; 

    // Evaluate triangle based on Inequality Theorem
    if ( inquality_theorem( tri ) != true ) return NotATriangle;

    // Check triangle type
    return check_type ( tri );

    int i=0;
    
}

int main( ) {

   //Simple Testing
    if ( isTriangle(Triangle(3,2,4)) != Scalene) { std::cout << "failed for <3,2,4>\n" << std::endl;}  

    if ( isTriangle(Triangle(5,4,3)) != Right) {std::cout << "failed for <5,4,3>\n" << std::endl;} 

    if ( isTriangle(Triangle(1,1,1)) != Equilateral) {std::cout << "failed for <1,1,1>\n" << std::endl;}

    if ( isTriangle(Triangle(-1,-1,-2)) != NotATriangle) {std::cout << "failed for <-1,-1,-2>\n" << std::endl;}

    if ( isTriangle(Triangle(3,2,4)) != Scalene) { std::cout << "failed for <3,2,4>\n" << std::endl;}

    if ( isTriangle(Triangle(4,4,6)) != Isosceles) {std::cout << "failed for <4,4,6>\n" << std::endl;}

    if ( isTriangle(Triangle(INT_MAX,INT_MAX,INT_MAX)) != NotATriangle) {std::cout << "failed for <-1,-1,-2>\n" << std::endl;}

    //Structured Testing
    std::vector <triangleTest> test_run;

    test_run.push_back(triangleTest((Triangle(1,2,3)), Scalene));
    test_run.push_back(triangleTest((Triangle(3,3,5)), Isosceles));
    test_run.push_back(triangleTest((Triangle(1,2,3)), Scalene));
    test_run.push_back(triangleTest((Triangle(4,-2,8)), NotATriangle));
    test_run.push_back(triangleTest((Triangle(3,5,7)), Scalene));
    test_run.push_back(triangleTest((Triangle(200,200,201)), Isosceles));
    test_run.push_back(triangleTest((Triangle(5,12,13)),Right));
    test_run.push_back(triangleTest(Triangle(35,612,613), Right));
    test_run.push_back(triangleTest(Triangle(23,264,265), Right));
    test_run.push_back(triangleTest(Triangle(2,2,2), Equilateral));


    // Testing with Random Numbers. 
    int x,y,z;
    unsigned seed = time(NULL);
    Triangle *test_tri = NULL; // dynamic memory for triangle



    srand(seed);
    //  Update, Random Testing of isTriangle
    

    for ( int i=0; i<100; i++ ) {
        x=rand() % 100 + 99 , y=rand() % 50 + 149, z=rand() % 20 + 179; // Generate the random integers

        test_tri = new Triangle(x,y,z); 

        if ( inquality_theorem(*test_tri)) { 

            test_run.push_back(triangleTest(*test_tri, Scalene));

            delete test_tri;
            test_tri = NULL;
        }
    }

    // Run the Test
    for ( int i=0; i< test_run.capacity(); i++) {
        runTest(test_run[i]);
    }

    return 0;

}