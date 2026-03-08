if(source == true)
{
	scalarField dist;
	if(line==true){
		 dimensionedVector dir = (p2-p1)/mag(p2-p1);
		 dist = sqrt(
                                        sqr(mesh.C().component(0)-(p1.component(0) + dir.component(0)*runTime*vel )) +
                                        sqr(mesh.C().component(1)-(p1.component(1) + dir.component(1)*runTime*vel )) +
                                        sqr(mesh.C().component(2)-(p1.component(2) + dir.component(2)*runTime*vel ))
                        );

	}
	else{
                 dist = sqrt(
                                        sqr(mesh.C().component(0)-center.component(0)) +
                                        sqr(mesh.C().component(1)-center.component(1)) +
                                        sqr(mesh.C().component(2)-center.component(2))
                        );
	}    
        forAll(pa,celli){
		if(dist[celli] <= radius.value()){

			//monopole source
			if(monopole==true){
				pa[celli] = amp.value()*Foam::sin(constant::mathematical::twoPi*fr.value()*runTime.value())/dist[celli]; 
			}
			//dipole source
			if(dipole==true){
				if(d.value()>2*radius.value()) Info<<" Poles out of source region"<<endl;
				vector dir; dimensionedVector dist_v("dist_v",dimless,vector::zero);
			       	dir.component(0)=Foam::sin(psi_.value())*Foam::cos(theta_.value());
				dir.component(1)=Foam::sin(psi_.value())*Foam::sin(theta_.value());
			       	dir.component(2)=Foam::cos(psi_.value());
				
				dist_v.component(0)=mesh.C()[celli].component(0)-center.value().component(0);
				dist_v.component(1)=mesh.C()[celli].component(1)-center.value().component(1);
				dist_v.component(2)=mesh.C()[celli].component(2)-center.value().component(2);
				dimensionedVector p1("p1",dimLength,center.value()+0.5*d.value()*dir);
				dimensionedVector p2("p2",dimLength,center.value()-0.5*d.value()*dir);
				
				scalar dangle = dir& dist_v.value()/dist[celli];
				       	scalar dp1 = Foam::sqrt(
                                        sqr(mesh.C()[celli].component(0)-p1.value().component(0)) +
                                        sqr(mesh.C()[celli].component(1)-p1.value().component(1)) +
                                        sqr(mesh.C()[celli].component(2)-p1.value().component(2))
		                        );
					scalar dp2 = Foam::sqrt(
                                        sqr(mesh.C()[celli].component(0)-p2.value().component(0)) +
                                        sqr(mesh.C()[celli].component(1)-p2.value().component(1)) +
                                        sqr(mesh.C()[celli].component(2)-p2.value().component(2))
                                        );
				
				pa[celli] = amp.value()*Foam::sin(constant::mathematical::twoPi*fr.value()*runTime.value());
				pa[celli] = pa[celli]/dp1 - pa[celli]/dp2;
			}
		
			//ricker dource
			if(ricker==true && runTime.value()<2*t0.value()){
				scalar omegaxtau = (runTime.value()-t0.value())*constant::mathematical::twoPi*fr.value();
				pa[celli] =  (1.0-0.5*Foam::sqr(omegaxtau))*Foam::exp(-0.25*Foam::sqr(omegaxtau))/dist[celli];
			}
		}
	}	
}
else{
	Info<<"NO SOURCE"<<endl;
	}
