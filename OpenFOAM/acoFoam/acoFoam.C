/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2019-2020 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
   acoFoam

Description
    Acoustic solver solving the acoustic pressure wave equation.
    It includes CPML variables and equations - to mimic open boundary conditions

    where
    \vartable
        cf      | Sound speed
	    rhof    | Density
        pa      | Acoustic pressure
    \endvartable

SourceFiles
    acoFoam.C


## Author 

    Andrea Petronio 
    https://www.researchgate.net/profile/Andrea-Petronio-2

    In collaboration with IE-FLuids Lab - University of Trieste, Trieste, Italy 
    https://dia.units.it/it/ricerca/node/90639


## Reference work

    Addeo, I., Petronio, A., Petris, G., Klin, P., & Cianferra, M. (2026). 
    Modeling underwater noise propagation: A comparative study of fully 3D Time-Domain numerical strategies. 
    Ocean Engineering, 354, 124887.

--> If you use this code for research or other purposes, please kindly cite this work
    
    Details of the model and its validation are presented in the paper


## Fundings

    BluEcho - From science to policy: assessing impacts and developing solutions for ship traffic and offshore wind farms through detailed soundmaps 
    Supported by the Sustainable Blue Economy Partnership. 
    
    SONORA - Filling the gap: Thresholds assessment and impact beyond acoustic pressure level linked to emerging blue-growth activities
    Project under the JPI Oceans (2022) Joint Call for Proposals on Underwater Noise in the Marine Environment

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "fvOptions.H"
#include "pimpleControl.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Acoustic solver solving the acoustic pressure wave equation."
    );

    #include "postProcess.H"

    #include "addCheckCaseOptions.H"
    #include "setRootCaseLists.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createControl.H"
    #include "createRegionControls.H"
    #include "createFields.H"

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.run())
    {
        ++runTime;

        Info<< "Time = " << runTime.timeName() << nl << endl;

        while (pimple.correct())
        {
            #include "paEqn.H"
        }

        runTime.write();
	    #include"softSource.H"
        runTime.printExecutionTime(Info);
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
