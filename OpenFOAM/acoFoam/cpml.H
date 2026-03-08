if(CPML==true) 
{
	Info << "\n CPML computing "<<endl;
	gradP = fvc::grad(pa);
        forAll(psi,cell)
        {
                psi[cell].component(vector::X) = a_x[cell] * psi[cell].component(vector::X) + b_x[cell]*gradP[cell].component(vector::X);
                psi[cell].component(vector::Y) = a_y[cell] * psi[cell].component(vector::Y) + b_y[cell]*gradP[cell].component(vector::Y);
                psi[cell].component(vector::Z) = a_z[cell] * psi[cell].component(vector::Z) + b_z[cell]*gradP[cell].component(vector::Z);
	}
	psi.correctBoundaryConditions();
	grad2P = fvc::grad(gradP);
	gradPsi = fvc::grad(psi); 
	grad2P.correctBoundaryConditions(); 
	gradPsi.correctBoundaryConditions();
	forAll(csi,celli){
		  csi[celli].component(vector::X) = a_x[celli] * csi[celli].component(vector::X) + b_x[celli]*(grad2P[celli].component(tensor::XX) + gradPsi[celli].component(tensor::XX));
                  csi[celli].component(vector::Y) = a_y[celli] * csi[celli].component(vector::Y) + b_y[celli]*(grad2P[celli].component(tensor::YY) + gradPsi[celli].component(tensor::YY));
	          csi[celli].component(vector::Z) = a_z[celli] * csi[celli].component(vector::Z) + b_z[celli]*(grad2P[celli].component(tensor::ZZ) + gradPsi[celli].component(tensor::ZZ));	
        }
        csi.correctBoundaryConditions();

}
