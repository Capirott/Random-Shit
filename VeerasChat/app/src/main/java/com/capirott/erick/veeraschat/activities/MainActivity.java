package com.capirott.erick.veeraschat.activities;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.managers.ChatUserManager;
import com.capirott.erick.veeraschat.models.ChatUser;
import com.firebase.ui.auth.AuthUI;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

public class MainActivity extends AppCompatActivity {

    private static final int RC_SIGN_IN = 123;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (FirebaseAuth.getInstance().getCurrentUser() != null) {
            loadNextActivity();
        } else {
            setContentView(R.layout.activity_main);
            configureButtonAnonymously();
            configureButtonLogin();
        }
    }

    void printWelcomeMessage() {
        FirebaseUser currentUser = FirebaseAuth.getInstance().getCurrentUser();
        if (currentUser != null) {
            String displayName = currentUser.getDisplayName();
            if (displayName == null || displayName.isEmpty()) {
                displayName = "Anon";
            }
            Toast.makeText(this, "Welcome " + displayName, Toast.LENGTH_LONG).show();
        } else {
            Log.d("MainActivity", "Error login in!");
        }
    }

    private void configureButtonLogin() {
        Button btnSignIn = (Button) findViewById(R.id.sign_in_button);
        btnSignIn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(FirebaseAuth.getInstance().getCurrentUser() == null) {
                    startActivityForResult(
                            AuthUI.getInstance()
                                    .createSignInIntentBuilder()
                                    .build(),
                           RC_SIGN_IN
                    );
                } else {
                    printWelcomeMessage();
                    loadNextActivity();
                }
            }
        });
    }

    private void configureButtonAnonymously() {
        Button btnSignAnonymously = (Button) findViewById(R.id.sign_in_anonymously);
        btnSignAnonymously.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FirebaseAuth.getInstance().signInAnonymously().addOnCompleteListener(MainActivity.this, new OnCompleteListener<AuthResult>() {
                    @Override
                    public void onComplete(@NonNull Task<AuthResult> task) {
                        if (task.isSuccessful()) {
                            printWelcomeMessage();
                            loadNextActivity();
                        } else {
                            Toast.makeText(MainActivity.this, "Authentication failed.",
                                    Toast.LENGTH_SHORT).show();
                        }
                    }
                });
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == RC_SIGN_IN) {
            if (resultCode == RESULT_OK) {
                printWelcomeMessage();
                loadNextActivity();
            } else {
                Log.d("MainActivity", "Error login in!");
            }
        }
    }

    private void loadNextActivity() {
        FirebaseUser currentUser = FirebaseAuth.getInstance().getCurrentUser();
        if (currentUser != null) {
            ChatUserManager.createOrUpdate(currentUser.getUid(), true);
            Log.d("VEERASCHAT", "Loading next activity");
//            Intent myIntent = new Intent(this, ConversationActivity.class);
            Intent myIntent = new Intent(this, RandomUserAcitivity.class);
            startActivity(myIntent);
            finish();
        } else {
            Log.e("MainActivity", "User not logged in!");
        }
    }
    }
