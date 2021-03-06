#include "stdafx.h"
#include "FzgFahren.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "dmath.h"
#include "Streckenende.h"

using namespace std;

FzgFahren::FzgFahren()
{
}

FzgFahren::FzgFahren(Weg * weg) : FzgVerhalten(weg, FzgVerhalten::Fahren)
{
}


FzgFahren::~FzgFahren()
{
}

double FzgFahren::dStrecke(Fahrzeug * fahrzeug, double zeit)
{
	double dIntStrecke = fahrzeug->dGeschwindigkeit() * zeit;
	double dWegPlatz = p_pWeg->dGetLength() - fahrzeug->dGetAbschnittStrecke();

	if (dmath::nearly_equal(dWegPlatz, 0))
	{
		throw Streckenende(fahrzeug, p_pWeg);
	}

	if (dWegPlatz < dIntStrecke)
	{
		return dWegPlatz;
	}
	if (this->p_pWeg->br_ueberholverbot())
	{
		double schranke = this->p_pWeg->p_lastexecuted->dGetAbschnittStrecke();
		double schrankeSpeed = this->p_pWeg->p_lastexecuted->dGetSpeed();
		if (fahrzeug->dGetAbschnittStrecke() + dIntStrecke > schranke && schrankeSpeed > 0.0)
		{
			double d_Abstand = schranke - fahrzeug->dGetAbschnittStrecke();
			//fahrzeug->SetSpeed(schrankeSpeed); TODO: RESET der Geschwindigkeit
			dIntStrecke = d_Abstand - 1;
		}
	}

	return dIntStrecke;
}
