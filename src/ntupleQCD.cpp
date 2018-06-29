/*
 * ntupleQCD.cpp
 *
 *  Created on: 24 Aug 2016
 *      Author: jkiesele
 */

#include "interface/ntupleQCD.h"



void ntupleQCD::analyze(size_t childid /* this info can be used for printouts */){

	/*
	 * This skeleton analyser runs directly on the Delphes output.
	 * It can be used to create histograms directly or a skim.
	 * If a skim is created, a new input configuration will be written automatically
	 * and stored in the output directory together with the ntuples.
	 * The skim can contain delphes objects again or can be flat. This is up
	 * to the user.
	 * Examples for both are given here.
	 *
	 * The same skeleton can be used to read the skim. Please refer to the comments
	 * marked with "==SKIM=="
	 *
	 * These parts are commented, since the code is supposed to work as an example without
	 * modifications on Delphes output directly.
	 */



	/*
	 * Define the branches that are to be considered for the analysis
	 * This branch handler (notice the "d")
	 * is used to run directly in Delphes output.
	 * For skimmed ntuples, see below
	 */
	d_ana::dBranchHandler<Electron> elecs(tree(),"Electron");
	/*
	 * Other branches might be the following
	 * (for a full list, please inspect the Delphes sample root file with root)
	 * For the Delphes class description, see $DELPHES_PATH/classes/DelphesClasses.h
	 */
	//
	d_ana::dBranchHandler<HepMCEvent>  event(tree(),"Event");
	d_ana::dBranchHandler<GenParticle> genpart(tree(),"Particle");
	d_ana::dBranchHandler<Jet>         genjet(tree(),"GenJet");
	d_ana::dBranchHandler<Jet>         jet(tree(),"Jet");
	d_ana::dBranchHandler<Muon>        muontight(tree(),"MuonTight");
	d_ana::dBranchHandler<Muon>        muonloose(tree(),"MuonLoose");
	//d_ana::dBranchHandler<Photon>      photon(tree(),"Photon");
	d_ana::dBranchHandler<MissingET>   met(tree(),"MissingET");


	/* ==SKIM==
	 *
	 * If a skim of the Delphes outout was created in a way indicated
	 * further below, use the tBranchHandler (please notive the "t")
	 * to access vectors of objects...
	 *
	 */
	// d_ana::tBranchHandler<std::vector<Electron> > electrons(tree(),"Electrons");

	/*==SKIM==
	 *
	 * Or an object directly
	 *
	 */
	//d_ana::tBranchHandler<MissingET> met(tree(),"MET");



	/*
	 * Always use this function to add a new histogram (can also be 2D)!
	 * Histograms created this way are automatically added to the output file
	 */
	//TH1* histo=addPlot(new TH1D("histoname1","histotitle1",100,0,100),"p_{T} [GeV]","N_{e}"); //commented PG


	/*
	 * If (optionally) a skim or a flat ntuple is to be created, please use the following function to initialize
	 * the tree.
	 * The output files will be written automatically, and a config file will be created.
	 */
	TTree* myskim=addTree();
	/*
	 * Add a simple branch to the skim
	 */
	std::vector<float> elecPt; 	std::vector<float> elecPhi; 	std::vector<float> elecEta; 
	std::vector<float> muonPt; 	std::vector<float> muonPhi; 	std::vector<float> muonEta; 
	myskim->Branch("elecPt","vector<float>" ,&elecPt);
	myskim->Branch("elecEta","vector<float>" ,&elecEta);
	myskim->Branch("elecPhi","vector<float>" ,&elecPhi);

	myskim->Branch("muonPt","vector<float>" ,&muonPt);
	myskim->Branch("muonEta","vector<float>" ,&muonEta);
	myskim->Branch("muonPhi","vector<float>" ,&muonPhi);

	//jets

        std::vector<float> pt_;         std::vector<float> btag_ ;         std::vector<float> eta_;           std::vector<float> phi_;         std::vector<float> mass_;          std::vector<float> massSoftDrop_;    std::vector<float> jetflavour_ ;
	std::vector<float> tau1_;       std::vector<float> tau2_;          std::vector<float> tau3_; 

	myskim->Branch("jetPt"                ,"vector<float>"     ,&pt_);
	myskim->Branch("jetBtag"              ,"vector<float>"     ,&btag_);  
	myskim->Branch("jetEta"               ,"vector<float>"     ,&eta_);
	myskim->Branch("jetPhi"               ,"vector<float>"     ,&phi_);
	myskim->Branch("jetMass"              ,"vector<float>"     ,&mass_);
	myskim->Branch("jetMassSoftDrop"      ,"vector<float>"     ,&massSoftDrop_);
	myskim->Branch("jetTau1"              ,"vector<float>"     ,&tau1_);
	myskim->Branch("jetTau2"              ,"vector<float>"     ,&tau2_);
	myskim->Branch("jetTau3" ,"vector<float>" ,&tau3_);
	myskim->Branch("jetFlavorHadron" ,"vector<float>" ,&jetflavour_);

	//gen jets

	std::vector<float> genjetpt_;         std::vector<float> genjetflavour_ ;         std::vector<float> genjeteta_;           std::vector<float> genjetphi_;         std::vector<float> genjetmass_;          std::vector<float> genjetmassSoftDrop_;    
	std::vector<float> genjettau1_;       std::vector<float> genjettau2_;          std::vector<float> genjettau3_; 

	
	myskim->Branch("genjetPt"                ,"vector<float>"     ,&genjetpt_);
	myskim->Branch("genjetFlavour"              ,"vector<float>"     ,&genjetflavour_);  
	myskim->Branch("genjetEta"               ,"vector<float>"     ,&genjeteta_);
	myskim->Branch("genjetPhi"               ,"vector<float>"     ,&genjetphi_);
	myskim->Branch("genjetMass"              ,"vector<float>"     ,&genjetmass_);
	myskim->Branch("genjetMassSoftDrop"      ,"vector<float>"     ,&genjetmassSoftDrop_);
	myskim->Branch("genjetTau1"              ,"vector<float>"     ,&genjettau1_);
	myskim->Branch("genjetTau2"              ,"vector<float>"     ,&genjettau2_);
	myskim->Branch("genjetTau3" ,"vector<float>" ,&genjettau3_);
	
	/*
	 * Or store a vector of objects (also possible to store only one object)
	 */
	//std::vector<Electron> skimmedelecs; //commented PG
	//myskim->Branch("Electrons",&skimmedelecs); //commented PG


	size_t nevents=tree()->entries();
	if(isTestMode())
		nevents/=100;
	for(size_t eventno=0;eventno<nevents;eventno++){
	  /*
	   * The following two lines report the status and set the event link
	   * Do not remove!
	   */
	  reportStatus(eventno,nevents);
	  tree()->setEntry(eventno);

	  /*
	   * Begin the event-by-event analysis
	   */
	  //commented by PG
	  //for(size_t i=0;i<elecs.size();i++){
	    //histo->Fill(elecs.at(i)->PT);
	  //}

	  /*
	   * Or to fill the skim
	   */
	  //skimmedelecs.clear(); //commented by PG
	  for(size_t i=0;i<elecs.size();i++){
	    //flat info
	    //added by PG
	    elecPt.push_back(elecs.at(i)->PT);
	    elecEta.push_back(elecs.at(i)->Eta); 
	    elecPhi.push_back(elecs.at(i)->Phi); 
	    //if(elecs.at(i)->PT < 20) continue;
	    //or objects
	    //skimmedelecs.push_back(*elecs.at(i)); //commented by PG
	  }

	  for(size_t i=0;i<muontight.size();i++){
	    //flat info
	    //added by PG
	    muonPt.push_back(muontight.at(i)->PT);
	    muonEta.push_back(muontight.at(i)->Eta); 
	    muonPhi.push_back(muontight.at(i)->Phi); 
	  }

	  for(size_t i=0;i<jet.size();i++){
	    //flat info
	    //added by PG
	    pt_.push_back(jet.at(i)->PT);
	    eta_.push_back(jet.at(i)->Eta); 
	    phi_.push_back(jet.at(i)->Phi); 
	    mass_.push_back(jet.at(i)->Mass); 
	    jetflavour_.push_back(jet.at(i)->Flavor);
	    btag_.push_back(jet.at(i)->BTag);
	  }

	  for(size_t i=0;i<genjet.size();i++){
	    //flat info
	    //added by PG
	    genjetpt_.push_back(genjet.at(i)->PT);
	    genjeteta_.push_back(genjet.at(i)->Eta); 
	    genjetphi_.push_back(genjet.at(i)->Phi); 
	    genjetmass_.push_back(genjet.at(i)->Mass);
	    genjetflavour_.push_back(genjet.at(i)->Flavor);
	    
	  }

	  myskim->Fill();
      //std::cout << "I am filling" << std::endl;

	  
	  /*==SKIM==
	   * Access the branches of the skim
	   */
	  //std::vector<Electron> * skimelecs=electrons.content();
	  //for(size_t i=0;i<skimelecs->size();i++){
	  //	histo->Fill(skimelecs->at(i).PT);
	  //}
	}

	
	/*
	 * Must be called in the end, takes care of thread-safe writeout and
	 * call-back to the parent process
	 */
	processEndFunction();
}



void ntupleQCD::postProcess(){
	/*
	 * This function can be used to analyse the output histograms, e.g. extract a signal contribution etc.
	 * The function can also be called directly on an output file with the histograms, if
	 * RunOnOutputOnly = true
	 * is set in the analyser's config file
	 *
	 * This function also represents an example of how the output of the analyser can be
	 * read-back in an external program.
	 * Just include the sampleCollection.h header and follow the procedure below
	 *
	 */

	/*
	 * Here, the input file to the extraction of parameters from the histograms is the output file
	 * of the parallelised analysis.
	 * The sampleCollection class can also be used externally for accessing the output consistently
	 */
  //d_ana::sampleCollection samplecoll;
  //	samplecoll.readFromFile(getOutPath());
  
  //	std::vector<TString> alllegends = samplecoll.listAllLegends();
  
  /*
   * Example how to process the output.
   * Usually, one would define the legendname of the histogram to be used here
	 * by hand, e.g. "signal" or "background".
	 * To make this example run in any case, I am using alllegends.at(0), which
	 * could e.g. be the signal legend.
	 *
	 * So in practise, the following would more look like
	 * samplecoll.getHistos("signal");
	 */
  //if(alllegends.size()>0){
  //d_ana::histoCollection histos=samplecoll.getHistos(alllegends.at(0));

		/*
		 * here, the histogram created in the analyze() function is selected and evaluated
		 * The histoCollection maintains ownership (you don't need to delete the histogram)
		 */
		//const TH1* myplot=histos.getHisto("histoname1"); //commented by PG

		//std::cout << "(example output): the integral is " << myplot->Integral() <<std::endl;

		/*
		 * If the histogram is subject to changes, please clone it and take ownership
		 */

		//TH1* myplot2=histos.cloneHisto("histoname1"); //commented by PG

		/*
		 * do something with the histogram
		 */

		//delete myplot2;
  //	}

	/*
	 * do the extraction here.
	 */



}



