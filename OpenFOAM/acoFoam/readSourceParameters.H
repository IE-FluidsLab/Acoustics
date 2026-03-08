Info<< "\nReading Sourc Parameters" << endl;

IOdictionary SourceParameters 
(
    IOobject
    (
        "SourceParameters",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);
bool source( SourceParameters.lookupOrDefault<Switch>("source",true));

// source type
bool monopole(SourceParameters.lookupOrDefault<Switch>("monopole",false));
bool dipole(SourceParameters.lookupOrDefault<Switch>("dipole",false));
bool ricker(SourceParameters.lookupOrDefault<Switch>("ricker",false));

// moving path
bool line( SourceParameters.lookupOrDefault<Switch>("line",false));

//source dimension 
dimensionedScalar radius("radius",dimLength, SourceParameters);

//source (initial) position
dimensionedVector center("center",dimLength, SourceParameters);

//monopole/dipole/quadrupole sources
dimensionedScalar amp("amp",dimensionSet(1,-1,-2,0,0),SourceParameters);
dimensionedScalar fr("fr",dimensionSet(0,0,-1,0,0),SourceParameters);

//dipole parameters
dimensionedScalar d("d",dimLength, SourceParameters);          //distance between poles
dimensionedScalar theta_("theta_",dimless, SourceParameters);  //orientation of poles azimut angle x-axe
dimensionedScalar psi_("psi_",dimless, SourceParameters);      //orientation of poles polar angle z-axe

//from degree to radians
psi_.value() = psi_.value()*Foam::constant::mathematical::pi/180;
theta_.value() = theta_.value()*Foam::constant::mathematical::pi/180;

//Ricker wavelet
dimensionedScalar t0("t0",dimTime,SourceParameters);

//moving source 
	    dimensionedVector  p1("p1",dimLength,SourceParameters);
        dimensionedVector  p2("p2",dimLength,SourceParameters);
        dimensionedScalar  vel("vel",dimVelocity,SourceParameters);
	Info << "\n Moving on line: point 1 "<< p1.value()<<" to point 2 "<<p2.value()<<" vel. "<< vel.value()<<endl;


Info << "\n Acoustic Source: center "<< center.value() <<" radius "<< radius.value()<< " amplitude "<<amp.value() << " freq. "<< fr.value()<< endl;
