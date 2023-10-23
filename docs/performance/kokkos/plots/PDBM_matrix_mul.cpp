Kokkos::parallel_for(TeamPolicyExec(num_elem, block_y, block_x), 
    KOKKOS_LAMBDA (const MemberTypeExec& team_member)
{
    int e = team_member.league_rank();

    Kokkos::parallel_for(Kokkos::TeamThreadRange(team_member, num_modes), 
        [=] (const int i)
    {
        Kokkos::parallel_for(Kokkos::ThreadVectorRange(team_member, q_b * q_c), 
            [=] (const int j)
        {
            double* A = Ba;
            double* B = u + e * (q_a * q_b * q_c);
            double* C = Hp + e * (L_a * q_b * q_c);

            double sum = 0.0;
            
            for (int k = 0; k < q_a; k++)
            {
                sum += A[i * q_a + k] * B[k * (q_b * q_c) + j];
            }
            
            C[i * (q_b * q_c) + j] = sum;
        });
    });
});

