llf anneal() {
  mt19937 rnd_engine( seed );
  uniform_real_distribution< llf > rnd( 0, 1 );
  const llf dT = 0.001;
  // Argument p
  llf S_cur = calc( p ), S_best = S_cur;
  for ( llf T = 2000 ; T > EPS ; T -= dT ) {
    // Modify p to p_prime
    const llf S_prime = calc( p_prime );
    const llf delta_c = S_prime - S_cur;
    llf prob = min( ( llf ) 1, exp( -delta_c / T ) );
    if ( rnd( rnd_engine ) <= prob )
      S_cur = S_prime, p = p_prime;
    if ( S_prime < S_best ) // find min
      S_best = S_prime, p_best = p_prime;
  }
  return S_best;
}
