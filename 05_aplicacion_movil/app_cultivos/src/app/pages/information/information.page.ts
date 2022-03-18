import { Component, OnInit } from '@angular/core';
import { CultivodbService } from './../../services/cultivodb.service'; //api REST
import { DatoPlanta } from './../../interfaces/dato-planta';

@Component({
  selector: 'app-information',
  templateUrl: './information.page.html',
  styleUrls: ['./information.page.scss'],
})

//setInterval(function(){alert('random_text')}, 3000);

export class InformationPage implements OnInit {

  
  bulb_plant_1:Boolean = false
  bulb_plant_2:Boolean = false
  bulb_plant_3:Boolean = false
  bulb_plant_4:Boolean = false

  humidity_plant_1:Boolean
  humidity_plant_2:Boolean
  humidity_plant_3:Boolean
  humidity_plant_4:Boolean

  temperature_1
  temperature_2
  temperature_3
  tempertaure_4

  arreglo_plantas: DatoPlanta[] = [];

//  temp_variable = this.arreglo_plantas[0]
//  var_x = this.temp_variable.Planta
//  var_x1 = this.temp_variable.Variable

  //if (this.var_x == '1') {

  //}





//poner el código que está en el ngOnInit dentro de un ciclo infinito (while true)
//para que se mantenga actualizando los datos y mostrandolos en la app

  constructor(private cultivodbService: CultivodbService) { }


//setInterval(fun(){alert('hello');}, 3000);
// this.cultivodbService.arregloPlantas()
//    .subscribe(plant_array => {
//      console.log(plant_array);
//      this.arreglo_plantas = plant_array; //:0
//    });


  ngOnInit() {
  	this.cultivodbService.arregloPlantas()
    .subscribe(plant_array => {
      console.log(plant_array);
      this.arreglo_plantas = plant_array; //:0
    });
  }

}
