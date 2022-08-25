if [ "$#" -ne 2 ]; then
        echo "Usage is: <keyword> <maxium_match> No argument provided"
else
        grep -r -n -i -m $2 $1 data

fi 
