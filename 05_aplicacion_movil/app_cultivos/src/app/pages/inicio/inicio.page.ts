import { Component, OnInit } from '@angular/core';
//import { CultivodbService } from './../../services/cultivodb.service'; //api REST
import { DatoPlanta } from './../../interfaces/dato-planta';

@Component({
  selector: 'app-inicio',
  templateUrl: './inicio.page.html',
  styleUrls: ['./inicio.page.scss'],
})

export class InicioPage implements OnInit {
  //estos son **fields** de la clase InicioPage
  usuario 
  prueba_ng: boolean = true

menu_list: MenuItem[] = [
  {
    icon: 'time-outline',
    name: 'Información Cultivos',
    redirectTo: '/information'
  },
  {
    icon: 'leaf-outline',
    name: 'Recomendaciones para el cultivo',
    redirectTo: '/recomendations'
  },
  {
    icon: 'business-outline',
    name: 'Sobre nosotros',
    redirectTo: '/about-us'
  },
  {
    icon: 'share-social-outline',
    name: 'Compartir',
    redirectTo: '/share'
  }
]

  constructor(/*private cultivodbService: CultivodbService base de datos*/) {
  }

/*
  ionViewDidLoad(){ //base de datos
  	this.servicio.obtenerDatos()
  	.subscribe(
  		(data)=> {this.usuario = data;}, //data y error son parámetros de una función lambda 
  		(error)=> {console.log(error);}  //(forma concisa de hacer una función anónima)
    )
  }

*/
  ngOnInit() {  }
}

interface MenuItem {
  icon: string;
  name: string;
  redirectTo: string;
}