#include <check.h>
#include <stdlib.h>
#include "biquad.h"


// START_TEST (biquad_lowpass_does_not_explode){
    
//     biquad_t filter;
//     AudioBlock input;
//     AudioBlock output;

//     filter = lowpass(220,0.5,48000);

//     for(int i = 0; i<BLOCKSIZE; i++){
//         input[i] = noise<double>();
//     }

//     std::tie(filter,output) = process<double>(filter,input);

//     for(int i = 0; i<BLOCKSIZE; i++){
//         EXPECT_GT(output[i],-1.0001);
//         EXPECT_LT(output[i],1.0001);
//     }
// }

START_TEST (biquad_lowpass_computes_coefficients)
{

    //biquad_t filter = lowpass(440, 0.5, 44100);
     /*
    https://www.earlevel.com/main/2010/12/20/biquad-calculator/
    EXPECTED FOR: cutoff = 220, q=0.5
    b0 = 0.00020151353208571057
    b1 = 0.00040302706417142114
    b2 = 0.00020151353208571057
    a1 = -1.943217815176137
    a2 = 0.9440238693044798
    */
    biquad_t filter;
    filter = algae__biquad.lowpass(220, 0.5, 48000);
    float epsilon = 0.000001;
    ck_assert_float_eq_tol( -1.943217815176137, filter.a1,  epsilon);
    ck_assert_float_eq_tol( 0.9440238693044798 , filter.a2,  epsilon);
    ck_assert_float_eq_tol( 0.00020151353208571057 , filter.b0,  epsilon);
    ck_assert_float_eq_tol( 0.00040302706417142114 , filter.b1,  epsilon);
    ck_assert_float_eq_tol( 0.00020151353208571057 , filter.b2,  epsilon);

   
}
END_TEST

Suite *biquad_suite(void) { 
    Suite *s;
    TCase *tc_core;

    s = suite_create("Biquad");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, biquad_lowpass_computes_coefficients);
    suite_add_tcase(s, tc_core); 

    return s;
} 

int main(void) {
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = biquad_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL); 
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE; 
} 
