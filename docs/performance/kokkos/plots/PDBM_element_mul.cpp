typedef Kokkos::Cuda Space;
typedef Kokkos::TeamPolicy<Space> TeamPolicyExec;
typedef Kokkos::TeamPolicy<Space>::member_type MemberTypeExec;

Kokkkos::parallel_for(TeamPolicyExec(num_elem, num_threads), 
    KOKKOS_LAMBDA (const MemberTypeExec& team_member)
{
    const int e = team_member.league_rank();

    Kokkos::parallel_for(Kokkos::TeamThreadRange(team_member, q_a * q_b * q_c),
        [=] (const int i)
    {
        u[e * (q_a * q_b * q_c) + i] *= wJ[i];
    });
});
