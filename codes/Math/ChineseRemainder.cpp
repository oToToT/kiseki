// ax+ny = 1, ax+ny == ax == 1 (mod n)
pair<lld,lld> gcd(lld a, lld b){
    if(b == 0) return {1, 0};
    pair<lld,lld> q = gcd(b, a % b);
    return {q.second, q.first - q.second * (a / b)};
}

lld crt(lld ans[], lld pri[], int n){
    lld M = 1;
    for(int i=0;i<n;i++) M *= pri[i];
    lld ret = 0;
    for(int i=0;i<n;i++){
        lld inv = (gcd(M/pri[i], pri[i]).first + pri[i])%pri[i];
        ret += (ans[i]*(M/pri[i])%M * inv)%M;
        ret %= M;
    }
    return ret;
}
