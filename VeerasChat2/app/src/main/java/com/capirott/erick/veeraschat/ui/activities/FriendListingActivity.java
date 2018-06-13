package com.capirott.erick.veeraschat.ui.activities;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.TabLayout;
import android.support.v4.view.ViewPager;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;

import com.capirott.erick.veeraschat.R;
import com.capirott.erick.veeraschat.ui.adapters.FriendListingPagerAdapter;

public class FriendListingActivity extends AppCompatActivity {
    private Toolbar mToolbar;
    private TabLayout mTabLayoutFriendListing;
    private ViewPager mViewPagerFriendListing;


    public static void startActivity(Context context) {
        Intent intent = new Intent(context, FriendListingActivity.class);
        context.startActivity(intent);
    }

    public static void startActivity(Context context, int flags) {
        Intent intent = new Intent(context, FriendListingActivity.class);
        intent.setFlags(flags);
        context.startActivity(intent);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_user_listing);
        bindViews();
        init();
    }

    private void bindViews() {
        mToolbar = (Toolbar) findViewById(R.id.toolbar);
        mTabLayoutFriendListing = (TabLayout) findViewById(R.id.tab_layout_user_listing);
        mViewPagerFriendListing = (ViewPager) findViewById(R.id.view_pager_user_listing);
    }

    private void init() {
        // set the toolbar
        setSupportActionBar(mToolbar);
        mToolbar.setTitle(R.string.friend_listing);
        // set the view pager adapter
        FriendListingPagerAdapter friendListingPagerAdapter = new FriendListingPagerAdapter(getSupportFragmentManager());
        mViewPagerFriendListing.setAdapter(friendListingPagerAdapter);

        // attach tab layout with view pager
        mTabLayoutFriendListing.setupWithViewPager(mViewPagerFriendListing);

    }

}
