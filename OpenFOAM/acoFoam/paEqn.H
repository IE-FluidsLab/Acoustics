#include"cplm.H"
cpml == gradPsi.component(tensor::XX) + gradPsi.component(tensor::YY) + gradPsi.component(tensor::ZZ) + csi.component(vector::X)+csi.component(vector::Y)+csi.component(vector::Z);
cpml.correctBoundaryConditions();

fvScalarMatrix paEqn
(
    fvm::d2dt2(pa) - sqr(cf)*(rhof*fvc::laplacian(1/rhof,pa) + cpml)
);
 
if (solvePrimaryRegion)
{
    paEqn.relax();
    paEqn.solve();
}
else
{
    pa.correctBoundaryConditions();
}
fvOptions.correct(pa);
