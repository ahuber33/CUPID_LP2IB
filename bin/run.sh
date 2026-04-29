for model in "glisur"
do
    for polish in 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0
    do
        ./OpticalSimulation output_"$model"_dielectric_dielectric_ground_"$polish" 1000 vrml.mac OFF "$model" dielectric_dielectric ground "$polish"
    done
done
