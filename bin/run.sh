for N in 0
do
    for cut in 0.00000001 0.0000001 0.000001 0.00001 0.0001 0.001 0.01 0.1 1.0 10.0
    do
    	until [ -e ../Resultats/cut/output_cut"$cut"mm.root ]
    	do
		./SCOPSim output_cut"$cut"mm 1000 vrml.mac OFF cut="$cut"
		mv ../Resultats/output_cut"$cut"mm.root ../Resultats/cut/
	done
    done
done
