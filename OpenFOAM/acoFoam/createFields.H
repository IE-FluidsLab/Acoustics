#include "readTransportProperties.H"
#include "readCPLMParameters.H"
#include "readSourceParameters.H"

Info << "\nReading pa" << endl;

volScalarField pa
(
    IOobject
    (
        "pa",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
volScalarField rhof
(
    IOobject
    (
        "rhof",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("rhof",dimensionSet(1,-3,0,0,0),rho.value()),
    "zeroGradient"
);
volScalarField cf
(
    IOobject
    (
        "cf",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("cf",dimVelocity,c0.value()),
    "zeroGradient"
);
// CPLM auxiliary fields
volVectorField psi
(
    IOobject
    (
        "psi",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedVector("psi",dimensionSet(1, -2, -2, 0, 0, 0, 0),vector(0.0, 0.0, 0.0)),
    "zeroGradient"
);

volVectorField csi
(
    IOobject
    (
        "csi",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedVector("csi",dimensionSet(1, -3, -2, 0, 0, 0, 0),vector::zero),
    "zeroGradient"
);
volScalarField cpml
(
    IOobject
    (
        "cpml",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("cpml",dimensionSet(1, -3, -2, 0, 0, 0, 0),0.0),
    "zeroGradient"
);
volTensorField gradPsi
(
    IOobject
    (
        "gradPsi",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedTensor("gradPsi",dimensionSet(1, -3, -2, 0, 0, 0, 0),tensor::zero),
    "zeroGradient"
);
volTensorField grad2P
(
    IOobject
    (
        "grad2P",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedTensor("grad2P",dimensionSet(1, -3, -2, 0, 0, 0, 0),tensor::zero),
    "zeroGradient"
);
volVectorField gradP
(
    IOobject
    (
        "gradP",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedVector("gradP",dimensionSet(1, -2, -2, 0, 0, 0, 0),vector::zero),
    "zeroGradient" 
);


scalarField a_x;
scalarField a_y;
scalarField a_z;

scalarField b_x;
scalarField b_y;
scalarField b_z;

if(CPLM==true){
        Info << "\n CPLM set-up ...  "<<endl;
 
	//Find the initial position of the colm region
        dimensionedScalar xL1=(max_lim.component(0)-L_damp.component(0));
        dimensionedScalar xL2=(min_lim.component(0)+Ln_damp.component(0));
        dimensionedScalar yL1=(max_lim.component(1)-L_damp.component(1));
        dimensionedScalar yL2=(min_lim.component(1)+Ln_damp.component(1));
        dimensionedScalar zL1=(max_lim.component(2)-L_damp.component(2));
        dimensionedScalar zL2=(min_lim.component(2)+Ln_damp.component(2));

        Info << "-->1 "<<xL1<<" "<<xL2<<" "<<yL1<<" "<<yL2<<""<<zL1<<" "<<zL2<<endl;
        scalarField cplm_x1 = pos(mesh.C().component(0)-xL1)*mag(mesh.C().component(0)-xL1)/L_damp.component(0); 
	scalarField cplm_y1 = pos(mesh.C().component(1)-yL1)*mag(mesh.C().component(1)-yL1)/L_damp.component(1);
        scalarField cplm_z1 = pos(mesh.C().component(2)-zL1)*mag(mesh.C().component(2)-zL1)/L_damp.component(2);
	
	scalarField cplm_x2 = neg(mesh.C().component(0)-xL2)*mag(mesh.C().component(0)-xL2)/Ln_damp.component(0);
        scalarField cplm_y2 = neg(mesh.C().component(1)-yL2)*mag(mesh.C().component(1)-yL2)/Ln_damp.component(1);
        scalarField cplm_z2 = neg(mesh.C().component(2)-zL2)*mag(mesh.C().component(2)-zL2)/Ln_damp.component(2);

        scalarField alphax1 = Foam::constant::mathematical::pi*f0.value()*(1-cplm_x1);
        scalarField alphay1 = Foam::constant::mathematical::pi*f0.value()*(1-cplm_y1);
        scalarField alphaz1 = Foam::constant::mathematical::pi*f0.value()*(1-cplm_z1);

	scalarField alphax2 = Foam::constant::mathematical::pi*f0.value()*(1-cplm_x2);
        scalarField alphay2 = Foam::constant::mathematical::pi*f0.value()*(1-cplm_y2);
        scalarField alphaz2 = Foam::constant::mathematical::pi*f0.value()*(1-cplm_z2);

        scalarField sigmax1 = (1.5*log(1/R_ref)*cf/L_damp.component(vector::X))*sqr(cplm_x1);
        scalarField sigmay1 = (1.5*log(1/R_ref)*cf/L_damp.component(vector::Y))*sqr(cplm_y1);
        scalarField sigmaz1 = (1.5*log(1/R_ref)*cf/L_damp.component(vector::Z))*sqr(cplm_z1);

	scalarField sigmax2 = (1.5*log(1/R_ref)*cf/Ln_damp.component(vector::X))*sqr(cplm_x2);
        scalarField sigmay2 = (1.5*log(1/R_ref)*cf/Ln_damp.component(vector::Y))*sqr(cplm_y2);
        scalarField sigmaz2 = (1.5*log(1/R_ref)*cf/Ln_damp.component(vector::Z))*sqr(cplm_z2);

	scalar deltat = mesh.time().deltaT().value();
        scalarField a_x1 = pos(cplm_x1)*exp(-(alphax1+sigmax1)*deltat);
        scalarField a_y1 = pos(cplm_y1)*exp(-(alphay1+sigmay1)*deltat);
        scalarField a_z1 = pos(cplm_z1)*exp(-(alphaz1+sigmaz1)*deltat);

	scalarField a_x2 = pos(cplm_x2)*exp(-(alphax2+sigmax2)*deltat);
        scalarField a_y2 = pos(cplm_y2)*exp(-(alphay2+sigmay2)*deltat);
        scalarField a_z2 = pos(cplm_z2)*exp(-(alphaz2+sigmaz2)*deltat);
	a_x = a_x1 + a_x2;
	a_y = a_y1 + a_y2;
	a_z = a_z1 + a_z2;
        b_x = pos(cplm_x1)*sigmax1*(a_x1-1)/(alphax1+sigmax1) + pos(cplm_x2)*sigmax2*(a_x2-1)/(alphax2+sigmax2);
        b_y = pos(cplm_y1)*sigmay1*(a_y1-1)/(alphay1+sigmay1) + pos(cplm_y2)*sigmay2*(a_y2-1)/(alphay2+sigmay2);
        b_z = pos(cplm_z1)*sigmaz1*(a_z1-1)/(alphaz1+sigmaz1) + pos(cplm_z2)*sigmaz2*(a_z2-1)/(alphaz2+sigmaz2);
	Info << "-------->6 "<<max(b_x)<<" "<<min(b_x)<<" "<<max(b_y)<<" "<<min(b_y)<<" "<<max(b_z)<<" "<<min(b_z)<<endl;
        Info << "\n ... done"<<endl;


volVectorField test
(
    IOobject
    (
        "test",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedVector("test",dimensionSet(1, -3, -2, 0, 0, 0, 0),vector(0,0,0))
);

forAll(test,celli){test[celli] = vector(b_x[celli],b_y[celli],b_z[celli]);}
test.write();

}
#include "createFvOptions.H"
