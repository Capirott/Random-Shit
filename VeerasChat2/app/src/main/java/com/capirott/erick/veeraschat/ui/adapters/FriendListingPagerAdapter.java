package com.capirott.erick.veeraschat.ui.adapters;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

import com.capirott.erick.veeraschat.ui.fragments.FriendsFragment;


public class FriendListingPagerAdapter extends FragmentPagerAdapter {
    private static final Fragment[] sFragments = new Fragment[]{/*UsersFragment.newInstance(UsersFragment.TYPE_CHATS),*/
            FriendsFragment.newInstance(FriendsFragment.TYPE_ALL)};
    private static final String[] sTitles = new String[]{/*"Chats",*/
            "All Friends"};

    public FriendListingPagerAdapter(FragmentManager fm) {
        super(fm);
    }

    @Override
    public Fragment getItem(int position) {
        return sFragments[position];
    }

    @Override
    public int getCount() {
        return sFragments.length;
    }

    @Override
    public CharSequence getPageTitle(int position) {
        return sTitles[position];
    }
}
