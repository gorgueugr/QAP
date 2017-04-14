#include "random.h"

int actual=4;
unsigned int r[4];






inline void rand_sse( unsigned int* result )

{

__m128i cur_seed_split;

__m128i multiplier;

__m128i adder;

__m128i mod_mask;

__m128i sra_mask;

__m128i sseresult;

static const unsigned int mult[4] =

{ 214013, 17405, 214013, 69069 };

static const unsigned int gadd[4] =

{ 2531011, 10395331, 13737667, 1 };

static const unsigned int mask[4] =

{ 0xFFFFFFFF, 0, 0xFFFFFFFF, 0 };

static const unsigned int masklo[4] =

{ 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF };



adder = _mm_load_si128( (__m128i*) gadd);

multiplier = _mm_load_si128( (__m128i*) mult);

mod_mask = _mm_load_si128( (__m128i*) mask);

sra_mask = _mm_load_si128( (__m128i*) masklo);

cur_seed_split = _mm_shuffle_epi32( cur_seed, _MM_SHUFFLE( 2, 3, 0, 1 ) );



cur_seed = _mm_mul_epu32( cur_seed, multiplier );

multiplier = _mm_shuffle_epi32( multiplier, _MM_SHUFFLE( 2, 3, 0, 1 ) );

cur_seed_split = _mm_mul_epu32( cur_seed_split, multiplier );


cur_seed = _mm_and_si128( cur_seed, mod_mask);

cur_seed_split = _mm_and_si128( cur_seed_split, mod_mask );

cur_seed_split = _mm_shuffle_epi32( cur_seed_split, _MM_SHUFFLE( 2, 3, 0, 1 ) );

cur_seed = _mm_or_si128( cur_seed, cur_seed_split );

cur_seed = _mm_add_epi32( cur_seed, adder);



// Add the lines below if you wish to reduce your results to 16-bit vals...

sseresult = _mm_srai_epi32( cur_seed, 16);

sseresult = _mm_and_si128( sseresult, sra_mask );

_mm_storeu_si128( (__m128i*) result, sseresult );

return;

}

void srand_sse( unsigned int seed )
{
cur_seed = _mm_set_epi32( seed, seed+1, seed, seed+1 );
}

int getRandom(){
  if(actual==4){
    actual=0;
    rand_sse(r);
    return (unsigned short) r[0];

  }
  ++actual;
  return ( unsigned short) r[actual];


}
int getRandomMax(int b){
  return (unsigned short) getRandomRange(0,b);
}

int getRandomRange(int a,int b){
  //return (unsigned short) (getRandom() % (b - a)) + a;
  //C=A%B; == C=A-((A/B)*B);
  //int divider  = b-a;
  //libdivide::divider<int> d(divider);
  int r=(unsigned short) getRandom();
  //int division=(r/d);
  uint32_t rem;
  libdivide::libdivide_64_div_32_to_32((uint32_t)0,(uint32_t)r,(uint32_t)b-a,&rem);
  return (unsigned short) rem + a;

  //return (unsigned short) (r - ( division * divider)) + a;

}
