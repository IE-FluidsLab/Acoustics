Info<< "\nReading CPLMParameters" << endl;

IOdictionary CPLMParameters 
(
    IOobject
    (
        "CPLMParameters",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);
bool CPLM( CPLMParameters.lookupOrDefault<Switch>("CPLM",true) );
dimensionedScalar f0("f0",dimensionSet(0, 0, -1, 0, 0), CPLMParameters);
dimensionedScalar R_ref("R_ref",dimless, CPLMParameters);
dimensionedVector L_damp("L_damp",dimLength,CPLMParameters);
dimensionedVector Ln_damp("Ln_damp",dimLength,CPLMParameters);

boundBox meshBb (mesh.bounds());
dimensionedVector max_lim("max_lim",dimLength,meshBb.max());
dimensionedVector min_lim("min_lim",dimLength,meshBb.min());
Info << "\n Bounding box for cplm damping " << endl;
Info << "X limits: "<<min_lim.component(0)<<" "<<max_lim.component(0)<<endl;
Info << "Y limits: "<<min_lim.component(1)<<" "<<max_lim.component(1)<<endl;
Info << "Z limits: "<<min_lim.component(2)<<" "<<max_lim.component(2)<<endl;
