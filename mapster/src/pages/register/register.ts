import { Component } from '@angular/core';
import { IonicPage, NavController, NavParams, ToastController } from 'ionic-angular';
import { Account } from '../../models/account';
import { AuthProvider } from '../../providers/auth/auth';

/**
 * Generated class for the RegisterPage page.
 *
 * See https://ionicframework.com/docs/components/#navigation for more info on
 * Ionic pages and navigation.
 */

@IonicPage()
@Component({
  selector: 'page-register',
  templateUrl: 'register.html',
})
export class RegisterPage {

  private account: Account;
  private confirmPassword: string;

  constructor(public navCtrl: NavController, public navParams: NavParams, private auth: AuthProvider, private toast: ToastController) {
    this.account = { email: "", password: "" };
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad RegisterPage');
  }

  async register() {
    if (this.validate()) {
      try {
        await this.auth.createUserWithEmailAndPassword(this.account);
        this.toast.create({ duration: 3000, message: "Account Created." }).present();
        this.navCtrl.pop();
      } catch (e) {
        this.toast.create({ duration: 3000, message: e.message }).present();
      }
    } else {
      this.toast.create({ duration: 3000, message: "Passwords do not match." }).present();
    }

  }

  validate() {
    return (this.account.email != "" && this.account.password != "" && this.confirmPassword != "" && (this.account.password === this.confirmPassword))
  }

}
