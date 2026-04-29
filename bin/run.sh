for model in "unified"
do
    for polish in 0.6
    do
        ./OpticalSimulation output_"$model"_dielectric_dielectric_ground_"$polish" 1000 vrml.mac OFF "$model" dielectric_dielectric ground "$polish"
    done
done
