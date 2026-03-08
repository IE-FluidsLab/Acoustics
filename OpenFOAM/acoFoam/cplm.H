if(CPLM==true) 
{
	Info << "\n CPLM computing "<<endl;
//        volVectorField gradP = fvc::grad(pa);
	gradP = fvc::grad(pa);
        forAll(psi,cell)
        {
                psi[cell].component(vector::X) = a_x[cell] * psi[cell].component(vector::X) + b_x[cell]*gradP[cell].component(vector::X);
                psi[cell].component(vector::Y) = a_y[cell] * psi[cell].component(vector::Y) + b_y[cell]*gradP[cell].component(vector::Y);
                psi[cell].component(vector::Z) = a_z[cell] * psi[cell].component(vector::Z) + b_z[cell]*gradP[cell].component(vector::Z);
	}
	psi.correctBoundaryConditions();
//	Info << "---------->7 "<<max(psi.component(0))<<" "<<min(psi.component(0))<<" "<<max(psi.component(1))<<" "<<min(psi.component(1))<<" "<<max(psi.component(2))<<" "<<min(psi.component(2))<<endl;
//	surfaceScalarField snGpa =fvc::snGrad(pa);
	grad2P = fvc::grad(gradP);
	gradPsi = fvc::grad(psi); 
	grad2P.correctBoundaryConditions(); 
	gradPsi.correctBoundaryConditions();
  //      Info << "------------>8 "<<max(mag(gradPsi))<<" "<<min(mag(gradPsi))<<" "<<max(mag(grad2P))<<" "<<min(mag(grad2P))<<" "<<max(mag(gradP))<<" "<<min(mag(gradP))<<endl;
  //	  Info << "------------>8 "<<max(csi.component(0))<<" "<<min(csi.component(0))<<" "<<max(csi.component(1))<<" "<<min(csi.component(1))<<" "<<max(csi.component(2))<<" "<<min(csi.component(2))<<endl; 
	forAll(csi,celli){
		  csi[celli].component(vector::X) = a_x[celli] * csi[celli].component(vector::X) + b_x[celli]*(grad2P[celli].component(tensor::XX) + gradPsi[celli].component(tensor::XX));
                  csi[celli].component(vector::Y) = a_y[celli] * csi[celli].component(vector::Y) + b_y[celli]*(grad2P[celli].component(tensor::YY) + gradPsi[celli].component(tensor::YY));
	          csi[celli].component(vector::Z) = a_z[celli] * csi[celli].component(vector::Z) + b_z[celli]*(grad2P[celli].component(tensor::ZZ) + gradPsi[celli].component(tensor::ZZ));	
        }
        csi.correctBoundaryConditions();
//	Info << "------------>8 "<<max(csi.component(0))<<" "<<min(csi.component(0))<<" "<<max(csi.component(1))<<" "<<min(csi.component(1))<<" "<<max(csi.component(2))<<" "<<min(csi.component(2))<<endl; 
//	gradP.write();
/*if(runTime.value()>0.01){
	grad2P.write();
	gradPsi.write();
}*/

}
