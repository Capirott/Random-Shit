package com.capirott.erick.veeraschat.core.registration;

import android.app.Activity;

import com.capirott.erick.veeraschat.models.User;
import com.google.firebase.auth.FirebaseUser;



public interface RegisterContract {
    interface View {
        void onRegistrationSuccess(FirebaseUser firebaseUser);

        void onRegistrationFailure(String message);
    }

    interface Presenter {
        void register(Activity activity, String email, String password);
        void registerAnonymously(Activity activity);
    }

    interface Interactor {
        void performFirebaseRegistration(Activity activity, String email, String password);

        void performFirebaseRegistrationAnonymously(Activity activity);
    }

    interface OnRegistrationListener {
        void onSuccess(FirebaseUser firebaseUser);

        void onFailure(String message);
    }
}
