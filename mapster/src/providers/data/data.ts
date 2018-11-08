import { Injectable } from '@angular/core';
import { Geoposition } from '@ionic-native/geolocation';
import { AngularFirestore } from 'angularfire2/firestore';
import { DateTime } from 'ionic-angular';
import { User } from '../../models/profile.interface';

/*
  Generated class for the DataProvider provider.

  See https://angular.io/guide/dependency-injection for more info on providers
  and Angular DI.
*/
@Injectable()
export class DataProvider {

  constructor(private data: AngularFirestore) {
    console.log('Hello DataProvider Provider');
  }

  async geoPush(geolist: Geoposition, uid: string) {
    try {
      await this.data.doc(`users/${uid}`).collection('locations').add({
        geo: [geolist.coords.latitude, geolist.coords.longitude],
        timestamp: (new Date).getTime()
      });
    } catch (error) {
      console.log(error);
      throw error;
    }
  }

  async createProfile(profile: User) {
    try {
      await this.data.collection<User>('users').add(profile);
    } catch (e) {
      console.log(e);
      throw e;
    }
  }
}
