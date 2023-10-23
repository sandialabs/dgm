// Create a view object that allocates data on the device
Kokkos::View<double*> array("array", num_elem);

// Launch a kernel and initialize the data
Kokkos::parallel_for(num_elements, KOKKOS_LAMBDA (const int i)
{
    array[i] = initial_value;
});
