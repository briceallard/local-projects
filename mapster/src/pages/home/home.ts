import { Component, ViewChild, ElementRef } from '@angular/core';
import { IonicPage, NavController, NavParams } from 'ionic-angular';
import { Geolocation } from '@ionic-native/geolocation';
import { DataProvider } from '../../providers/data/data';
import { AuthProvider } from '../../providers/auth/auth';


declare var google;

@IonicPage()
@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {

  @ViewChild('map') mapElement: ElementRef;
  map: any;
  private uid: string;

  constructor(public navCtrl: NavController, public geolocation: Geolocation, private data: DataProvider, private auth: AuthProvider) {
    this.auth.getAuthenticatedUser()
      .then((user) => this.uid = user.uid);
  }

  ionViewDidLoad() {
    this.loadMap();
  }

  async loadMap() {

    let position = await this.geolocation.getCurrentPosition();

    let latLng = new google.maps.LatLng(position.coords.latitude, position.coords.longitude);
    console.log(position.coords.latitude);
    console.log(position.coords.longitude);
    var lat = position.coords.latitude;
    var lon = position.coords.longitude;

    try {
      await this.data.geoPush(position, this.uid);
    } catch (error) {
      console.log(error);
    }

    let mapOptions = {
      center: latLng,
      zoom: 15,
      mapTypeId: google.maps.MapTypeId.ROADMAP
    }

    this.map = new google.maps.Map(this.mapElement.nativeElement, mapOptions);



  }

  async logout() {
    await this.auth.logout();
    this.navCtrl.setRoot('LoginPage');
  }

  addMarker() {

    let marker = new google.maps.Marker({
      map: this.map,
      animation: google.maps.Animation.DROP,
      position: this.map.getCenter()
    });

    let content = "<h4>Information!</h4>";

    this.addInfoWindow(marker, content);

  }

  addInfoWindow(marker, content) {

    let infoWindow = new google.maps.InfoWindow({
      content: content
    });

    google.maps.event.addListener(marker, 'click', () => {
      infoWindow.open(this.map, marker);
    });

  }

}
