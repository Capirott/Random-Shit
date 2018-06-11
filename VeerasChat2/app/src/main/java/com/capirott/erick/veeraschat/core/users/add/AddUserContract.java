package com.capirott.erick.veeraschat.core.users.add;

import android.content.Context;

import com.capirott.erick.veeraschat.models.User;
import com.google.firebase.auth.FirebaseUser;



public interface AddUserContract {
    interface View {
        void onAddUserSuccess(String message);

        void onAddUserFailure(String message);
    }

    interface Presenter {
        void addUser(Context context, User user);
    }

    interface Interactor {
        void addUserToDatabase(Context context, User user);
    }

    interface OnUserDatabaseListener {
        void onSuccess(String message);

        void onFailure(String message);
    }
}
