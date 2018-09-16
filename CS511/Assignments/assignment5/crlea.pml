/*Jennifer Cafiero & Kaitlynn Prescott
  I pledge my honor that I have abided by the Stevens Honor System*/

#define N   5
#define L   10
byte I;

mtype = { one, two, winner };
chan q[N] = [L] of { mtype, byte };

proctype nnode(chan inp, out; byte mynumber) {
    bit Active = 1, know_winner = 0;
    byte nr, maximum = mynumber, neighbourR;

    xr inp; /* channel assertion: exlusive rcv access to channel in */
    xs out; /* channel assertion: exclusive send access to channel out */

    printf("MSC: %d\n", mynumber);
    out ! one(mynumber);

end:
    do
    :: inp?one(nr) ->
        if
        :: Active ->
            if
            :: nr == mynumber ->
                Active = 0;
                know_winner = 1;
                out ! winner, nr;
            :: nr > mynumber->
                Active = 0;
                out ! one, nr;
            :: else ->
                skip;
            fi;
        :: else ->
            out ! one(nr);
        fi;
    :: inp?winner, nr ->
        printf("I am node %d and I know the leader is %d", mynumber, nr);
        if
        :: know_winner
        :: else -> out ! winner, nr
        fi;
        break;
    od;
}


init {
    byte proc;
    byte Ini[6];
    atomic {
        I = 1;
        do
        :: I <= N ->
            if
            :: Ini[0] == 0 && N >= 1 -> Ini[0] = I
            :: Ini[1] == 0 && N >= 2 -> Ini[1] = I
            :: Ini[2] == 0 && N >= 3 -> Ini[2] = I
            :: Ini[3] == 0 && N >= 4 -> Ini[3] = I
            :: Ini[4] == 0 && N >= 5 -> Ini[4] = I
            :: Ini[5] == 0 && N >= 6 -> Ini[5] = I
            fi;
            I++;
        :: I > N ->
            break;
        od;

        proc = 1;
        do
        :: proc <= N ->
            run nnode(q[proc - 1], q[proc % N], Ini[proc - 1]);
            proc++;
        :: proc > N ->
            break;
        od;
    }
}
